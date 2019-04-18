#! /usr/bin/python

### https://docs.python.org/2/library/xml.etree.elementtree.html

import re
import getopt
import sys
import serial
import subprocess
import xml.etree.ElementTree as ET

class CMD:
   def __init__(self, name, val):
      self.name = name
      self.val = val
      
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
def parse_cmd(str):
  
  words = str.split('_')
  send_cmd = []             #temp list to store commands to send
  
#  for word in words:       #go through each word in splitted line
#    for cmd in cmds:       #compare word to each supported command
#      if word[0] == cmd.function_code:   #is the word any of the supported commands in cmds
#         tmp_word = cmd.callback(word)  #call command-specific handler, i.e parse command
#         if tmp_word != '':
#            send_cmd.append(tmp_word) #add command to send-message, send_cmd is a list of strings
#
#  return ''.join(send_cmd) #join will append the list of strings to one string
  
 
### start of main script #############################################

in_file = ''
debug = 1
#port = '/dev/ttyS2'
in_file = 'config/axis_mm.ini'

f_in = open(in_file, 'r')

# parse for .xml-file
for line in f_in:
   if 'ARPY_MPG' in line:     
      # remove comment if any
      i = line.find('#')
      if i >= 0:
         line = line[:i]
      
      # get the file name
      i = line.find('=')
      if i >= 0:
         line = line[i+1:]
         
      # remove blank-spaces
      line = line.strip(' ')
      
      # remove line ending
      xml_file = line.strip('\n')

   if 'SERIAL_PORT' in line:  
      # remove comment if any
      i = line.find('#')
      if i >= 0:
         line = line[:i]

      # get the name
      i = line.find('=')
      if i >= 0:
         line = line[i+1:]

      # remove blank-spaces
      line = line.strip(' ')

      # remove line ending
      port = line.strip('\n')
   
print 'xml: ' + xml_file   
print 'port: ' + port
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

if debug == 0:
   try:
      ser.open() #ser = serial.Serial(port = 'COM3', baudrate=9600, bytesize=8, parity='N', stopbits=1, timeout=3)
   except serial.SerialException as e:
      sys.stderr.write('{} {}\n'.format(ser.name, e))
      #sys.stderr.write('Could not open serial port {}: {}\n'.format(ser.name, e))
      subprocess.call("echo available ports:", shell=True) 
      subprocess.call("python -m serial.tools.list_ports", shell=True) 
      sys.exit(1)


h = hal()
h.component("mpg")

tree = ET.parse(xml_file)
root = tree.getroot()
      
for halpin in root.iter('halpin'):
   type = halpin.find('type')
   event = halpin.find('event')
   
   if type is not None and event is not None:
      #print 'l'+halpin.text + 'r', type.text, event.text
      h.newpin(halpin.text, type.text, hal.HAL_OUT)

for pin in h.pin_list:
   #print pin.name, pin.type
   print h[pin.name].name

 #ser.write(''.join(str).encode('utf-8'))
 #ser.write('\n')
 #serial expects a byte-array and not a string
if debug == 0:
   if ser.in_waiting:
      b = ser.read_until() #blocks until '\n' received or timeout
      parse_cmd(b.Decode('utf-8'))
      
