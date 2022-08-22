#! /usr/bin/python
"""usage serialEventHanlder.py -h -c <name> -d/--debug= <level> -p/--port= <serial port> <path/>in_file.xml
in_file  -  input xml-file describing what knobs and/or button are on the pendant
-c <name>                # name of component in HAL. 'my-mpg' default
-d/--debug= <level>      # debug level, default 0
-p/--port= <serial port> # serial port to use. '/dev/ttyUSB0' default
-h                       # Help 
python serialEventHandler.py -w mpg_pendant/config/mpg.xml
"""

### https://docs.python.org/2/library/xml.etree.elementtree.html

import time
import getopt
import sys
import comms
import xml.etree.ElementTree as ET
import hal

class Pin:
   """ General representation of a Pin and it's data"""
   def __init__(self, name, type, direction = 'out'):
      self.name = name  # HAL pin name
      self.val = 0    # current value of pin, e.g. 1 - on, 0 - off
      self.type = type  # type (string read from xml)
      self.direction = direction

   def __repr__(self):
      return 'pin name: ' + self.name + '\tval: ' + str(self.val) + '\ttype: ' + self.type + '\tdirection: ' + self.direction

   def update(self, v):
      """ to be overriden in child-class"""
      pass

class InPin(Pin):
   """ Specialization of Pin-class"""
   def __init__(self, name, type):
      Pin.__init__(self, name, type, 'in')

   def update(self, v):
      self.val = v

class OutPin(Pin):
   """ Specialization of Pin-class"""
   def __init__(self, name, type):
      Pin.__init__(self, name, type, 'out')

   def update(self, v):
      pass #v = self.val

class ComponentWrapper:   
   def __init__(self, name):
      self.pin_dict = {}       # dictionary used to map event to pin
      self.hal = hal.component(name)  # instanciate the HAL-component
         
   def __repr__(self):
      tmp_str = ''
      for k in self.pin_dict:
         tmp_str += 'event: ' + k + '\t' + str(self.pin_dict[k]) + '\n'
      return tmp_str

   def __getitem__(self, name):
      if name in self.pin_dict:
         return self.pin_dict[name].val

   def __setitem__(self, name, val):
      self.set_pin(name, val)

   def add_pin(self, name, hal_name, type, direction = 'out'):
      self.pin_dict[name] = self._createPin(hal_name, type, direction) 
      self._add_hal_pin(hal_name, type, direction)

   def event_set_pin(self, event):
      """ updates pin value with new data
      input: pin name, set value' 
      output: nothing. """
      if event.name in self.pin_dict:
         try:
            self.pin_dict[event.name].val = self._type_saturate(self.pin_dict[event.name].type, int(event.data))
         except ValueError:
            print 'bad event: ' + event.name  
            

   def set_pin(self, name, value):
      """ updates pin value with new data
      input: pin name, set value' 
      output: nothing. """
      if name in self.pin_dict:
         try:
            self.pin_dict[name].val = self._type_saturate(self.pin_dict[name].type, int(value))
         except ValueError:
            print 'bad event' + name  
            
   def setReady(self):
      self.hal.ready()
            
   def update_hal(self):
      for key in self.pin_dict:
         if self.pin_dict[key].direction == 'out':
            self.hal[self.pin_dict[key].name] = self.pin_dict[key].val

         if self.pin_dict[key].direction == 'in':
            self.pin_dict[key].update(self.hal[self.pin_dict[key].name])
         #   self.pin_dict[key].val = self.hal[self.pin_dict[key].name]

   def _createPin(self, name, type, direction):
      """ factory function to create pin"""
      if direction == 'in':
         return InPin(name, type)
      if direction == 'out':
         return OutPin(name, type)

   def _add_hal_pin(self, hal_name, type, direction = 'out'):
      self.hal.newpin(hal_name, self._get_hal_type(type), self._get_hal_direction(direction))  # create the user space HAL-pin

   def _type_saturate(self, type, val):
      """ helper function to convert type read from xml to HAL-type """
      retVal = 0
   
      if type == 'bit':
         if val >= 1:
            retVal = 1
	
      if type == 'float':
         retVal = val

      if type == 's32':
         retVal = val

      if type == 'u32':
         retVal = val
               
      return retVal      

   def _get_hal_type(self, str):
      """ helper function to convert type read from xml to HAL-type """
      retVal = ''
   
      if str == 'bit':
         retVal = hal.HAL_BIT
	
      if str == 'float':
         retVal = hal.HAL_FLOAT

      if str == 's32':
         retVal = hal.HAL_S32

      if str == 'u32':
         retVal = hal.HAL_U32

      return retVal 

   def _get_hal_direction(self, direction):
      """ helper function to convert pin-direction read from xml to HAL-direction """
      retVal = ''

      if direction == 'out':
         retVal = hal.HAL_OUT

      if direction == 'in':
         retVal = hal.HAL_IN
      
      return retVal

class OptParser:
   def __init__(self, argv):
      self.xml_file = ''   # input xml-file describing what knobs and/or button are on the pendant
      self.name = 'my-mpg'       # default name of component in HAL
      self.port = '/dev/ttyUSB0' # default serial port to use
      self.watchdog_reset = False

      self._get_options(argv)
      
   def __repr__(self):
      return 'xml_file: ' + self.xml_file + '\tname: ' + self.name + '\tport: ' + self.port
      
   def _get_options(self, argv):
      try:
         opts, args = getopt.getopt(argv, "hwp:c:", ["input=", "port="])
      except getopt.GetoptError as err:
         # print help information and exit:
         print(err) # will print something like "option -a not recognized"
         sys.exit(2)

      ### parse input command line
      for o, a in opts:
         if o == "-h":
            self._usage()
            sys.exit()
         if o == "-c":
            self.name = a
         elif o == "--input":
            self.xml_file = a
         elif o in ("-p", "--port"):
            self.port = a
         elif o == "-w":
            self.watchdog_reset = True
         else:
            print o, a
            assert False, "unhandled option"
      
      if self.xml_file == '':
         if len(sys.argv) < 2:
            self._usage()
            sys.exit(2)
         else:
            self.xml_file = argv[-1]
               
   def get_name(self):
      return self.name

   def get_port(self):
      return self.port

   def get_XML_file(self):
      return self.xml_file
   
   def get_watchdog_reset(self):
      return self.watchdog_reset

   def _usage(self):
      """ print command line options """
      print "usage serialEventHandler.py -h -c <name> -d/--debug=<level> -p/--port= <serial port> <path/>in_file.xml\n"\
         "in_file  -  input xml-file describing what knobs and/or button are on the pendant\n"\
         "-c <name>                # name of component in HAL. 'mpg' default\n"\
         "-p/--port= <serial port> # default serial port to use. '/dev/ttyS2' default\n"\
         "-w                       # start watchdog deamon" \
         "-h                       # Help test"

class XmlParser:
   def __init__(self, f):
      self.tree = []
      self.pin_dict = {}
      
      self._parse_file(f)
      
   def __repr__(self):
      tmp_str = ''

      for k in self.pin_dict:
         tmp_str += 'event: ' + k + '\t' + str(self.pin_dict[k]) + '\n'
      return tmp_str   
      
   def get_parsed_data(self):
      return self.pin_dict
   
   def _parse_file(self, f):
      self.tree = ET.parse(f)
      root = self.tree.getroot()
            
      for halpin in root.iter('halpin'):
         type = halpin.find('type')
         event = halpin.find('event')
         direction = halpin.find('direction')

         # create the LinuxCNC hal pin and create mapping dictionary binding incomming events with data and the hal pins
         if type is not None and event is not None and self._check_supported_HAL_direction(direction.text):
            if self._check_supported_HAL_type(type.text) == True:
               self.pin_dict[event.text] = Pin(halpin.text.strip('"'), type.text, direction.text)
   
   def _check_supported_HAL_type(self, str):
      """ helper function to check if type is supported """
      retVal = False
   
      if str == 'bit' or str == 'float' or str == 's32' or str == 'u32':
         retVal = True
         
      return retVal 

   def _check_supported_HAL_direction(self, str):
      """ helper function to check if direction is supported """
      retVal = False
   
      if str == 'in' or str == 'out':
         retVal = True

      return retVal 

class BrokeeContainer:
   def __init__(self, handler, args):
      self.handler = handler
      self.args = args

class EventBroker:
   def __init__(self):
      self.brokee_dict = {}
      self.received_event = comms.Message('')

   def attach_handler(self, event_name, handler, args = ()):
      self.brokee_dict[event_name] = BrokeeContainer(handler, args)

   def handle_event(self, event):
      self.received_event.copy(event)

      if event.name in self.brokee_dict:            
         self.brokee_dict[event.name].handler(*self.brokee_dict[event.name].args)

################################################
def main():
   optParser = OptParser(sys.argv[1:])
   componentName = optParser.get_name()
   portName = optParser.get_port()
   xmlFile = optParser.get_XML_file()
   watchdogEnable = optParser.get_watchdog_reset()
   print optParser
      
   xmlParser = XmlParser(xmlFile)

   c = ComponentWrapper(componentName) #HAL adaptor
   eventBroker = EventBroker() #maps incomming events to the correct handler
   serialEventGenerator = comms.instrument(portName, eventBroker.handle_event, watchdogEnable, 5, 1) #serial adaptor

   # add/create the HAL-pins from parsed xml and attach them to the adaptor event handler
   parsedXmlDict = xmlParser.get_parsed_data()
   for key in parsedXmlDict:
      c.add_pin(key, parsedXmlDict[key].name, parsedXmlDict[key].type)
      eventBroker.attach_handler(key, c.event_set_pin, args = (eventBroker.received_event,))
      # TODO eventBroker.attach_handler(key, c.set_pin, args = (eventBroker.received_event.name, eventBroker.received_event.data))
   
   print c

   # ready signal to HAL, component and it's pins are ready created
   c.setReady()
      
   try:
      while 1:
         serialEventGenerator.readMessages() #blocks until '\n' received or timeout
         c.update_hal()

         time.sleep(0.05)

   except KeyboardInterrupt:
      raise SystemExit

if __name__ == '__main__':
   main()
