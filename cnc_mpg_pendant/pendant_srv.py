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
      
## handler for G-words. only G0 and G1 currently supported
def handle_g(str):
   retVal = ''

   if (str == 'G0' or str == 'G00'): 
      retVal = 'G0'
      
   if (str == 'G1' or str == 'G01'):
      retVal = 'G1'
      
   if (str == 'G28'):
      retVal = 'G28'
      
   if (str == 'G92'):
      retVal = 'G92'
      
   if (str == 'G52'):
      retVal = 'G52'

   return retVal

## handler for X-words, converts from mm to 10um unit
def handle_x(in_str):
   tmp_f = float(in_str[1:len(in_str)])
   tmp_i = int(round(tmp_f*100))
   ret_str = 'X' + str(tmp_i)
   return ret_str

## handler for Y-words
def handle_y(in_str):
   tmp_f = float(in_str[1:len(in_str)])
   tmp_i = int(round(tmp_f*100))
   ret_str = 'Y' + str(tmp_i)
   return ret_str
   
## handler for Z-words
def handle_z(in_str):
   tmp_f = float(in_str[1:len(in_str)])
   tmp_i = int(round(tmp_f*100))
   ret_str = 'Z' + str(tmp_i)
   return ret_str
   
## handler for F-words
def handle_f(in_str):
   try:
      ret_str = 'F' + str(int(in_str[1:len(in_str)]))
   except ValueError:
      ret_str = ''

   return ret_str
   
## handler for M-words
def handle_m(str):
   try:
      ret_str = 'M' + str(int(in_str[1:len(in_str)]))
   except ValueError:
      ret_str = ''

   return ret_str
   
### parse_line() #############################################
def parse_cmd(str):
  
  words = str.split()
  send_cmd = []             #temp list to store commands to send
  
  for word in words:       #go through each word in splitted line
    for cmd in cmds:       #compare word to each supported command
      if word[0] == cmd.function_code:   #is the word any of the supported commands in cmds
         tmp_word = cmd.callback(word)  #call command-specific handler, i.e parse command
         if tmp_word != '':
            send_cmd.append(tmp_word) #add command to send-message, send_cmd is a list of strings

  return ''.join(send_cmd) #join will append the list of strings to one string
  
  
## wait for character ch sent from client ################################## 
def waitForToken(ch):
   if debug == 0:
      b = ser.read(1) #blocking
      print 'rec: ' + b
      if ser.in_waiting:
         while b != ch:
            print b
            b = ser.read(1)
   
   if debug == '1':
      s = raw_input('\tpress any key:') 
 
### start of main script #############################################

#these are the accepted commands everything else will be thrown away
cmds = [CMD('G', handle_g), CMD('X', handle_x), CMD('Y', handle_y), CMD('Z', handle_z), CMD('F', handle_f), ]

in_file = ''
debug = 1
port = '/dev/ttyS2'

try:
  opts, args = getopt.getopt(sys.argv[1:], "h", ["input=", "debug=", "port="])
except getopt.GetoptError as err:
  # print help information and exit:
  print(err) # will print something like "option -a not recognized"
  sys.exit(2)

for o, a in opts:
  if o == "-h":
    print 'usage pendant_srv.py --input=<in.xml> --debug=[012] --port=<serial port>'
    sys.exit()
  elif o == "--input":
    in_file = a
  elif o == "--debug":
    debug = a
  elif o == "--port":
    port = a
  else:
    print o
    assert False, "unhandled option"

if in_file == '':
   print 'usage pendant_srv.py --input=<in.xml> --debug=[012] --port=<serial port>'
   sys.exit()

# open serial port
# list available ports with 'python -m serial.tools.list_ports'
ser = serial.Serial()
ser.port = port
ser.baudrate = 9600
ser.parity = 'N'
ser.bytesize = 8
ser.stopbits = 1
ser.xonxoff = False       #disable software flow control
#ser.rtscts = False       #disable hardware (RTS/CTS) flow control
#ser.dsrdtr = False       #disable hardware (DSR/DTR) flow control
#ser.writeTimeout = 2     #timeout for write
#ser.timeout = 3

if debug == 0:
   try:
      ser.open() #ser = serial.Serial(port = 'COM3', baudrate=9600, bytesize=8, parity='N', stopbits=1, timeout=3)
   except serial.SerialException as e:
      sys.stderr.write('{} {}\n'.format(ser.name, e))
      #sys.stderr.write('Could not open serial port {}: {}\n'.format(ser.name, e))
      subprocess.call("echo available ports:", shell=True) 
      subprocess.call("python -m serial.tools.list_ports", shell=True) 
      sys.exit(1)


tree = ET.parse(in_file)
root = tree.getroot()
      
for halpin in root.iter('halpin'):
   type = halpin.find('type')
   event = halpin.find('event')
   
   if type is not None and event is not None:
      print halpin.text, type.text, event.text
      