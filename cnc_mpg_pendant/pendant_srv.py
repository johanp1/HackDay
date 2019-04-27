#! /usr/bin/python

### https://docs.python.org/2/library/xml.etree.elementtree.html

#import re
import time
import getopt
import sys
import serial
import subprocess
import xml.etree.ElementTree as ET

class Pin:
   """ Representation of a Pin and it's data"""
   def __init__(self, name, val, type):
      self.name = name
      self.val = val
      self.type = type
      
class hal_pin:
   """stub sub class to hal-class"""
   
   def __init__(self, name, type):
      self.name = name
      self.type = type

class hal:
   """stub class linuxCNC hal-api"""
   HAL_BIT = 'HAL_BIT'
   HAL_S32 = 'HAL_S32'
   HAL_U32 = 'HAL_U32'
   HAL_OUT = 'HAL_OUT'
   
   pin_list = []
   ready_flag = 0;
   def component(self, name):
      self.name = name
   def newpin(self, pin_name, pin_type, dir):
      self.pin_list.append(hal_pin(pin_name.strip('"'), pin_type))
   def ready():
      ready = 1
   def __getitem__(self, name):
      for pin in self.pin_list:
         if pin.name == name:
            return pin
   
   
### parse_line() #############################################
def updatePin(str):
   """parses incomming cmd and update Pin data value accordingly"""
   cmd = str.split('_')
   if len(cmd) == 2:
      val = cmd[1] 
      ev = cmd[0]
  
      event2PinDict[ev].val = int(val)
      print ev + ' ' + val
  
def usage():
   print 'usage pendant_srv.py -c name <path/>in_file.xml'
  
### start of main script #############################################

xml_file = ''
name = ''
debug = 1
port = '/dev/ttyS2'

try:
  opts, args = getopt.getopt(sys.argv[1:], "hpd:c:", ["input=", "port=", "debug="])
except getopt.GetoptError as err:
  # print help information and exit:
  print(err) # will print something like "option -a not recognized"
  sys.exit(2)

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
   name = 'mpg'

print 'xml: ' + xml_file   
print 'port: ' + port
print 'name: ' + name
print 'debug: ' + str(debug)

# open serial port
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

event2PinDict = {}
h = hal()
h.component(name)

tree = ET.parse(xml_file)
root = tree.getroot()
      
for halpin in root.iter('halpin'):
   type = halpin.find('type')
   event = halpin.find('event')
   
   # create the LinuxCNC hal pin and create mapping dictionary binding incomming events with data and the hal pins
   if type is not None and event is not None:
      #print 'l'+halpin.text + 'r', type.text, event.text
      h.newpin(halpin.text, type.text, hal.HAL_OUT)
      event2PinDict[event.text] = Pin(halpin.text.strip('"'), 0, type) #dictionary to map between event and hal_pin in h
 

#serial expects a byte-array and not a string
if debug == '0':
   
   ser.flush()

   while 1:
      if ser.in_waiting:
         b = ser.read_until() #blocks until '\n' received or timeout
         #print b
         updatePin(b.decode('utf-8'))
      
      time.sleep(0.01)  
      
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
   