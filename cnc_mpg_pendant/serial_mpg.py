"""usage serial_mpg.py -h -c <name> -d/--debug= <level> -p/--port= <serial port> <path/>in_file.xml
in_file  -  input xml-file describing what knobs and/or button are on the pendant
-c <name>                # name of component in HAL. 'my-mpg' default
-d/--debug= <level>      # debug level, default 0
-p/--port= <serial port> # serial port to use. '/dev/ttyUSB0' default
-h                       # Help 
"""

#! /usr/bin/pythone

### https://docs.python.org/2/library/xml.etree.elementtree.html

import time
import getopt
import sys
import comms
import xml.etree.ElementTree as ET
import hal

class Pin:
   """ Representation of a Pin and it's data"""
   def __init__(self, name, type):
      self.name = name  # HAL pin name
      self.val = 0    # current value of pin, e.g. 1 - on, 0 - off
      self.type = type  # type (string read from xml)

   def __repr__(self):
      return 'pin name: ' + self.name + '\tval: ' + str(self.val) + '\ttype: ' + self.type
   
class ComponentWrapper:   
   def __init__(self, name):
      self.evToHALPin = {}            # dictionary used to map event to pin
      self.hal = hal.component(name)  # instanciate the HAL-component

   def __repr__(self):
      tmp_str = ''
      for k in self.evToHALPin:
         tmp_str += 'event: ' + k + '\t' + str(self.evToHALPin[k]) + '\n'
      return tmp_str
      
   def addPin(self, ev_name, pin_name, type):
      if self._getHALType(type) != '':
         self.evToHALPin[ev_name] = Pin(pin_name, type) # dictionary to map between event and HAL-pin
         self.hal.newpin(pin_name, self._getHALType(type), hal.HAL_OUT)  # create the user space HAL-pin

   def updatePin(self, e):
      """ updates pin value with new event data
      input: event object' 
      output: nothing. """
      if e.ev in self.evToHALPin:
         self.evToHALPin[e.ev].val = self._typeSaturate(self.evToHALPin[e.ev].type, int(e.val))
            
   def setReady(self):
      self.hal.ready()
            
   def updateHAL(self):
      for key in self.evToHALPin:
         self.hal[self.evToHALPin[key].name] = self.evToHALPin[key].val

         
   def _getHALType(self, str):
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

   def _typeSaturate(self, type, val):
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


class OptParser:
   def __init__(self, argv):
      self.xml_file = ''   # input xml-file describing what knobs and/or button are on the pendant
      self.name = 'my-mpg'       # default name of component in HAL
      self.port = '/dev/ttyUSB0' # default serial port to use

      print argv
      
      self._getOptions(argv)
      
   def __repr__(self):
      return 'xml_file: ' + self.xml_file + '\tname: ' + self.name + '\tport: ' + self.port
      
   def _getOptions(self, argv):
      try:
         opts, args = getopt.getopt(argv, "hp:c:", ["input=", "port="])
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
         else:
            print o
            assert False, "unhandled option"
      
      if self.xml_file == '':
         if len(sys.argv) < 2:
            self._usage()
            sys.exit(2)
         else:
            self.xml_file = argv[-1]
               
   def getName(self):
      return self.name

   def getPort(self):
      return self.port

   def getXmlFile(self):
      return self.xml_file
   
   def _usage(self):
      """ print command line options """
      print "usage pendant_srv.py -h -c <name> -d/--debug= <level> -p/--port= <serial port> <path/>in_file.xml\n"\
         "in_file  -  input xml-file describing what knobs and/or button are on the pendant\n"\
         "-c <name>                # name of component in HAL. 'mpg' default\n"\
         "-p/--port= <serial port> # default serial port to use. '/dev/ttyS2' default\n"\
         "-h                       # Help test";

class XmlParser:
   def __init__(self, f):
      self.tree = []
      self.dataDict = {}
      
      self._parseFile(f)
      
   def getParsedData(self):
      #self.data = ['jog-counts', 'jog', 's32']
      print self.dataDict
      return self.dataDict
   
   def _parseFile(self, f):
      self.tree = ET.parse(f)
      root = self.tree.getroot()
            
      for halpin in root.iter('halpin'):
         type = halpin.find('type')
         event = halpin.find('event')
      
         # create the LinuxCNC hal pin and create mapping dictionary binding incomming events with data and the hal pins
         if type is not None and event is not None:
            print event.text + ' ' + halpin.text.strip('"') + ' ' + type.text
            self.dataDict[event.text] = halpin.text.strip('"')
      
      
### start of main script #############################################
def main():
   optParser = OptParser(sys.argv[1:])
   componentName = optParser.getName()
   portName = optParser.getPort()
   xmlFile = optParser.getXmlfile()
   print optParser
   
   c = ComponentWrapper(componentName)
   serialMpg = comms.instrument(portName, c.updatePin)

   xmlParser = XmlParser(xmlFile)
   
   tree = ET.parse(optParser.getXmlFile())
   root = tree.getroot()
         
   # iterate the xml to find the knobs/buttons on the pendant, their event names, type and HAL-pin-name
   for halpin in root.iter('halpin'):
      type = halpin.find('type')
      event = halpin.find('event')
      
      # create the LinuxCNC hal pin and create mapping dictionary binding incomming events with data and the hal pins
      if type is not None and event is not None:
         #print 'l'+halpin.text + 'r', type.text, event.text
         c.addPin(event.text, halpin.text.strip('"'), type.text)

   # ready signal to HAL, component and it's pins are ready created
   c.setReady()
   
   print c

   try:
      while 1:
         serialMpg.readEvents() #blocks until '\n' received or timeout
         c.updateHAL()
            
         time.sleep(0.05)

   except KeyboardInterrupt:
      raise SystemExit

if __name__ == '__main__':
   main()
