"""usage pendant_srv.py -h -c <name> -d/--debug= <level> -p/--port= <serial port> <path/>in_file.xml
in_file  -  input xml-file describing what knobs and/or button are on the pendant
-c <name>                # name of component in HAL. 'mpg' default
-d/--debug= <level>      # debug level
-p/--port= <serial port> # default serial port to use. '/dev/ttyS2' default
-h                       # Help test
"""

#! /usr/bin/python

### https://docs.python.org/2/library/xml.etree.elementtree.html

import time
import getopt
import sys
import subprocess
import xml.etree.ElementTree as ET
import hal
import comms

class Pin:
   """ Representation of a Pin and it's data"""
   def __init__(self, pin_name, curr_val, type):
      self.name = pin_name  # HAL pin name
      self.val = curr_val    # current value of pin, e.g. 1 - on, 0 - off
      self.type = type  # HAL type

class ComponentWrapper:   
   def __init__(self, name):
      self.evToHALPin = {}
      self.hal = hal.component(name)  # instanciate the HAL-component

      
   def addPin(self, ev_name, pin_name, type):
      if self._getHALType(type) != '':
         self.evToHALPin[ev_name] = Pin(pin_name, 0, type) # dictionary to map between event and hal_pin in h
         self.hal.newpin(pin_name, self._getHALType(type), hal.HAL_OUT)                    # create the user space HAL-pin

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
      

  
### start of main script #############################################
def main():
   xml_file = ''  # input xml-file describing what knobs and/or button are on the pendant
   name = ''      # name of component in HAL
   port = '/dev/ttyS2' #default serial port to use
   
   try:
     opts, args = getopt.getopt(sys.argv[1:], "hp:d:c:", ["input=", "port="])
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
      
   if name == '':
      name = 'mpg' # default name

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
      
      # create the LinuxCNC hal pin and create mapping dictionary binding incomming events with data and the hal pins
      if type is not None and event is not None:
         #print 'l'+halpin.text + 'r', type.text, event.text
         c.addPin(event.text, halpin.text.strip('"'), type)

   c.setReady()

   ### serial expects a byte-array and not a string
   while 1:
         
      serialmpg.readEvents() #blocks until '\n' received or timeout
      c.updateHAL()
      
      time.sleep(0.05)  
      
if __name__ == '__main__':
   main()
