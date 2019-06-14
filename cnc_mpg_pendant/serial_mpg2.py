"""usage serial_mpg.py -h -c <name> -d/--debug= <level> -p/--port= <serial port> <path/>in_file.xml
in_file  -  input xml-file describing what knobs and/or button are on the pendant
-c <name>                # name of component in HAL. 'my-mpg' default
-d/--debug= <level>      # debug level, default 0
-p/--port= <serial port> # serial port to use. '/dev/ttyACM0' default
-h                       # Help 
"""

#! /usr/bin/python

### https://docs.python.org/2/library/xml.etree.elementtree.html

import time
import getopt
import sys
import comms
import subprocess
import xml.etree.ElementTree as ET
import hal

class Pin:
   """ Representation of a Pin and it's data"""
   def __init__(self, name, val, type):
      self.name = name  # HAL pin name
      self.val = val    # current value of pin, e.g. 1 - on, 0 - off
      self.type = type  # type (string read from xml)

class ComponentWrapper:   
   def __init__(self, name):
      self.evToHALPin = {}            # dictionary used to map event to pin
      self.hal = hal.component(name)  # instanciate the HAL-component

      
   def addPin(self, ev_name, pin_name, type):
      if self._getHALType(type) != '':
         self.evToHALPin[ev_name] = Pin(pin_name, 0, type) # dictionary to map between event and HAL-pin
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
      
def usage():
   """ print command lie options """
   print "usage pendant_srv.py -h -c <name> -d/--debug= <level> -p/--port= <serial port> <path/>in_file.xml\n"\
         "in_file  -  input xml-file describing what knobs and/or button are on the pendant\n"\
         "-c <name>                # name of component in HAL. 'mpg' default\n"\
         "-p/--port= <serial port> # default serial port to use. '/dev/ttyS2' default\n"\
         "-h                       # Help test";

  
### start of main script #############################################

xml_file = ''         # input xml-file describing what knobs and/or button are on the pendant
name = 'my-mpg'       # default name of component in HAL
port = '/dev/ttyACM0' # default serial port to use

try:
  opts, args = getopt.getopt(sys.argv[1:], "hp:d:c:", ["input=", "port=", "debug="])
except getopt.GetoptError as err:
  # print help information and exit:
  print(err) # will print something like "option -a not recognized"
  sys.exit(2)

### parse input command line
for o, a in opts:
  if o == "-h":
    usage()
    sys.exit()
  if o == "-c":
    name = a
  elif o == "--input":
    xml_file = a
  elif o in ("-p", "--port"):
    port = a
  else:
    print o
    assert False, "unhandled option"
   
if xml_file == '':
   if len(sys.argv) < 2:
      usage()
      sys.exit(2)
   else:
      xml_file = sys.argv[-1]
   
print 'xml: ' + xml_file   
print 'port: ' + port
print 'name: ' + name

c = ComponentWrapper()
serialmpg = comms.instrument(port, c.updatePin)
   
### parse input xml file

tree = ET.parse(xml_file)
root = tree.getroot()
      
# iterate the xml to find the knobs/buttons on the pendant, their event names, type and HAL-pin-name
for halpin in root.iter('halpin'):
   type = halpin.find('type')
   event = halpin.find('event')
   
   # create the LinuxCNC HAL pin and create mapping dictionary binding incomming events with data and the HAL pins
   if type is not None and event is not None:
      HALpin_name = halpin.text.strip('"')
      HALpin_type = _getHALType(type.text)
      
      print 'creating HAL pin ' + halpin.text.strip('"') + ' of type ' + type.text
      c.addPin(event.text, halpin.text.strip('"'), type)
      
# ready signal to HAL, component and it's pins are ready created 
c.setReady()

# main loop
try:
   while 1:
      serialmpg.readEvents() #blocks until '\n' received or timeout
      c.updateHAL()
         
      time.sleep(0.05)

except KeyboardInterrupt:
   raise SystemExit
