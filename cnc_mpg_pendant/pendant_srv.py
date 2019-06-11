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
   def __init__(self, name, val, type):
      self.name = name  # HAL pin name
      self.val = val    # current value of pin, e.g. 1 - on, 0 - off
      self.type = type  # HAL type
   
def _is_number(s):
   """  helper function to evaluate if input is an integer or not """
   try:
      int(s)
      return True
   except ValueError:
      return False
   
### parse_line() #############################################
def updatePin(e):
   """parses incomming cmd and update Pin data value accordingly
   input: command string, formated as: '<event>_<number>\n' 
   output: nothing.
   """

   if e.ev in event2PinDict and _is_number(e.val):
         event2PinDict[e.ev].val = int(e.val)
         print e.ev + ' ' + e.val
  
def usage():
   print "usage pendant_srv.py -h -c <name> -d/--debug= <level> -p/--port= <serial port> <path/>in_file.xml\n"\
         "in_file  -  input xml-file describing what knobs and/or button are on the pendant\n"\
         "-c <name>                # name of component in HAL. 'mpg' default\n"\
         "-p/--port= <serial port> # default serial port to use. '/dev/ttyS2' default\n"\
         "-h                       # Help test";

  
### start of main script #############################################

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

serialmpg = comms.instrument(port)

### parse input xml file
event2PinDict = {} # dictionary. data-key is the event name sent from Pendant, data-element object containing HAL-pin-name, type and current value
h = hal.component(name)  # instanciate the component

tree = ET.parse(xml_file)
root = tree.getroot()
      
# iterate the xml to find the knobs/buttons on the pendant, their event names, type and HAL-pin-name
for halpin in root.iter('halpin'):
   type = halpin.find('type')
   event = halpin.find('event')
   
   # create the LinuxCNC hal pin and create mapping dictionary binding incomming events with data and the hal pins
   if type is not None and event is not None:
      #print 'l'+halpin.text + 'r', type.text, event.text
      h.newpin(halpin.text, type.text, hal.HAL_OUT)                    # create the user space HAL-pin
      event2PinDict[event.text] = Pin(halpin.text.strip('"'), 0, type) # dictionary to map between event and hal_pin in h
 
h.ready()

### serial expects a byte-array and not a string
   
while 1:
      
   events = serialmpg.readEvents() #blocks until '\n' received or timeout
   
   #handle new events
   if len(events) != 0: 
      for e in events:
         updatePin(e)
     
   time.sleep(0.05)  
