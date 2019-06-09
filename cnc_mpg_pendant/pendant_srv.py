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
import serial
import subprocess
import xml.etree.ElementTree as ET
import hal

class Pin:
   """ Representation of a Pin and it's data"""
   def __init__(self, name, val, type):
      self.name = name  # HAL pin name
      self.val = val    # current value of pin, e.g. 1 - on, 0 - off
      self.type = type  # HAL type
   
def is_number(s):
   """  helper function to evaluate if input is an integer or not """
   try:
      int(s)
      return True
   except ValueError:
      return False
   
### parse_line() #############################################
def updatePin(str):
   """parses incomming cmd and update Pin data value accordingly
   input: command string, formated as: '<event>_<number>\n' 
   output: nothing.
   """
   cmd = str.split('_')
   if len(cmd) == 2:
      val = cmd[1] 
      ev = cmd[0]
      if ev in event2PinDict and is_number(val):
         event2PinDict[ev].val = int(val)
         print ev + ' ' + val
  
def usage():
   print "usage pendant_srv.py -h -c <name> -d/--debug= <level> -p/--port= <serial port> <path/>in_file.xml\n"\
         "in_file  -  input xml-file describing what knobs and/or button are on the pendant\n"\
         "-c <name>                # name of component in HAL. 'mpg' default\n"\
         "-d/--debug= <level>      # debug level\n" \
         "-p/--port= <serial port> # default serial port to use. '/dev/ttyS2' default\n"\
         "-h                       # Help test";

  
### start of main script #############################################

xml_file = ''  # input xml-file describing what knobs and/or button are on the pendant
name = ''      # name of component in HAL
debug = 1      # debug level
port = '/dev/ttyS2' #default serial port to use

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
  elif o in ("-d", "--debug"):
   debug = a
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
print 'debug: ' + str(debug)

### open serial port
# list available ports with 'python -m serial.tools.list_ports'
ser = serial.Serial()
ser.port = port
ser.baudrate = 9600
ser.parity = 'N'
ser.bytesize = 8
ser.stopbits = 1
ser.xonxoff = False       # disable software flow control
#ser.rtscts = False       # disable hardware (RTS/CTS) flow control
#ser.dsrdtr = False       # disable hardware (DSR/DTR) flow control
#ser.writeTimeout = 2     # timeout for write
ser.timeout = 1           # 1 sec timeout

if debug == '0':
   try:
      ser.open() #ser = serial.Serial(port = 'COM3', baudrate=9600, bytesize=8, parity='N', stopbits=1, timeout=3)
   except serial.SerialException as e:
      sys.stderr.write('{} {}\n'.format(ser.name, e))
      #sys.stderr.write('Could not open serial port {}: {}\n'.format(ser.name, e))
      subprocess.call("echo available ports:", shell=True) 
      subprocess.call("python -m serial.tools.list_ports", shell=True) 
      sys.exit(1)

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
if debug == '0':
   
   ser.flush()

   while 1:
      while ser.in_waiting:
         b = ser.read_until() #blocks until '\n' received or timeout
         #print b
         updatePin(b.decode('utf-8'))
      
      time.sleep(0.05)  
      
### test... ###################################
for evKey in event2PinDict:
   p = event2PinDict[evKey]
   print 'event: ' + evKey + ' halpin: ' + p.name
#   print h[p.name].name
   
#for pin in h.pin_list:
   #print pin.name, pin.type
#   print h[pin.name].name
cmds = ['sel_1', 'sel_3', 'jog_10', 'run_1', 'run_0', 'rth_1', 'rth_0', ]
#ser.write(''.join(str).encode('utf-8'))
#ser.write('\n')
 
for cmd in cmds:
   updatePin(cmd)
   for evKey in event2PinDict:
      p = event2PinDict[evKey]
      print 'halpin: ' + p.name + ' data: ' + str(p.val)
#################################################   