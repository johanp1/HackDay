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
   def __init__(self, name, pinDict):
      self.evToHALPin = pinDict       # dictionary used to map event to pin
      self.hal = hal.component(name)  # instanciate the HAL-component

      for key in self.evToHALPin:
         self._addHALPin(self.evToHALPin[key].name, self.evToHALPin[key].type)
         
   def __repr__(self):
      tmp_str = ''
      for k in self.evToHALPin:
         tmp_str += 'event: ' + k + '\t' + str(self.evToHALPin[k]) + '\n'
      return tmp_str

   def addPin(self, event, name, type):
      self.evToHALPin[event] = Pin(name, type) 
      self._addHALPin(name, type)

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

   def _addHALPin(self, pin_name, type):
      #self.evToHALPin[ev_name] = Pin(pin_name, type) # dictionary to map between event and HAL-pin
      self.hal.newpin(pin_name, self._getHALType(type), hal.HAL_OUT)  # create the user space HAL-pin

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
      self.pinDict = {}
      
      self._parseFile(f)
      
   def __repr__(self):
      tmp_str = ''

      for k in self.pinDict:
         tmp_str += 'event: ' + k + '\t' + str(self.pinDict[k]) + '\n'
      return tmp_str   
      
   def getParsedData(self):
      return self.pinDict
   
   def _parseFile(self, f):
      self.tree = ET.parse(f)
      root = self.tree.getroot()
            
      for halpin in root.iter('halpin'):
         type = halpin.find('type')
         event = halpin.find('event')
      
         # create the LinuxCNC hal pin and create mapping dictionary binding incomming events with data and the hal pins
         if type is not None and event is not None:
            if self._checkSupportedHALType(type.text) == True:
               self.pinDict[event.text] = Pin(halpin.text.strip('"'), type.text) 
      
   def _checkSupportedHALType(self, str):
      """ helper function to check if type is supported """
      retVal = False
   
      if str == 'bit' or str == 'float' or str == 's32' or str == 'u32':
         retVal = True
         
      return retVal 
      
### start of main script #############################################
def main():
   pinDict = {}
   
   optParser = OptParser(sys.argv[1:])
   componentName = optParser.getName()
   portName = optParser.getPort()
   xmlFile = optParser.getXmlFile()
   print optParser
      
   xmlParser = XmlParser(xmlFile)
      
   c = ComponentWrapper(componentName, xmlParser.getParsedData())
   c.addPin("hb", "heart-beat", "u32")
   print c
   
   serialMpg = comms.instrument(portName, c.updatePin)
   
   # ready signal to HAL, component and it's pins are ready created
   c.setReady()
   
   try:
      while 1:
         serialMpg.readEvents() #blocks until '\n' received or timeout
         c.updateHAL()
            
         time.sleep(0.05)

   except KeyboardInterrupt:
      raise SystemExit

if __name__ == '__main__':
   main()
