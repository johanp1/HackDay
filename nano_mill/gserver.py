#! /usr/bin/python

'''
G90, for absolute position mode.
G80, to cancel any previously used canned cycles.
G28, to rapid to the home position.
G17, to select the x, y circular motion field.
G20, to select the inch coordinate system. (G21, to select metric)
G40, to cancel cutter compensation.
G49, to cancel the cutter height compensation.

G00, rapid move to a position
G01, linear cut from current position to programmed X, Y, Z
G02, moves the cutter along a clock wise arc until the current position is the new programmed position
G03, moves the cutter along a counter-clock wise arc until the current position is the new programmed position

N## G## X## Y## Z## F## S## T## M##

N: Line number
G: Motion
X: Horizontal position
Y: Vertical position
Z: Depth
F: Feed rate (units/minute. units, G20 for inch, G21 for metric)
S: Spindle speed
T: Tool selection
M: Miscellaneous functions
I and J: Incremental center of an arc
R: Radius of an arc 

Miscellaneous Codes

    M00: Program stop
    M01: Optional program stop
    M02: End of program
    M03: Spindle on clockwise
    M04: Spindle on counterclockwise
    M05: Spindle stop
    M06: Tool change
    M08: Flood coolant on
    M09: Flood coolant off
    M30: End of program/return to start
    M41: Spindle low gear range
    M42: Spindle high gear range
'''

import re
import getopt
import sys
import serial

class CMD:
   def __init__(self, function_code, callback):
      self.function_code = function_code
      self.callback = callback
      
## handler for G-words. only G0 and G1 currently supported
def handle_g(str):
   retVal = ''

   if (str == 'G0' or str == 'G00'): 
      retVal = 'G0'
      
   if (str == 'G1' or str == 'G01'):
      retVal = 'G1'
      
   if (str == 'G28'):
      retVal = 'G28'

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
def parse_line(str):
  
  words = str.split()
  send_cmd = []             #temp list to store commands to send
  
  for word in words:       #go through each word in splitted line
    for cmd in cmds:       #compare word to each supported command
      if word[0] == cmd.function_code:   #is the word any of the supported commands in cmds
         tmp_word = cmd.callback(word)  #call command-specific handler, i.e parse command
         if tmp_word != '':
            send_cmd.append(tmp_word) #add command to send-message, send_cmd is a list of strings

  return ''.join(send_cmd) #join will append the list of strings to one string
  
  
### send_line() ############################################# 
def send_data(str, f_hdlr):

   print '\tsending: ' +  str

   if debug == 0:
      ser.write(''.join(str).encode('utf-8'))
      ser.write('\n')
      #serial expects a byte-array and not a string
          
   if debug == '2':
      f_hdlr.write(' '.join(str))  #join will append the list of strings to one string
      f_hdlr.write('\n')
  
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

#these are the accepted/supported G-codes, everything else will be thrown away
cmds = [CMD('G', handle_g), CMD('X', handle_x), CMD('Y', handle_y), CMD('Z', handle_z), CMD('F', handle_f), ]

in_file = ''
out_file = ''
debug = 0

try:
  opts, args = getopt.getopt(sys.argv[1:], "h", ["input=", "output=", "debug="])
except getopt.GetoptError as err:
  # print help information and exit:
  print(err) # will print something like "option -a not recognized"
  sys.exit(2)

for o, a in opts:
  if o == "-h":
    print 'usage gserver.py --input=<in.ngc> --output=<out.txt> --node=[RC]CIOM'
    sys.exit()
  elif o == "--input":
    in_file = a
  elif o == "--output":
    out_file = a
  elif o == "--debug":
    debug = a
  else:
    print o
    assert False, "unhandled option"

if in_file == '':
   print 'usage gserver.py --input=<in.log> --output=<out.txt>'
   sys.exit()
   
if out_file == '':
   out_file = 'out.txt'
   print 'using default log file out.txt'

f_in = open(in_file,'r')
f_out = open(out_file,'w')

# open serial port
# list available ports with 'python -m serial.tools.list_ports'
ser = serial.Serial()
ser.port = '/dev/ttyS2'
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
      sys.stderr.write('Could not open serial port {}: {}\n'.format(ser.name, e))
      sys.exit(1)

#wait for # sent from client indicating it is done with it's init, before sending first command line
waitForToken('#')      
      
line = f_in.readline()
while line != '':
   print 'processing: ' + line
   send_str = parse_line(line) 

   if send_str != '':
      send_data(send_str, f_out)

	  #do not send next line if not confirmed by client/user
	  waitForToken('*')
         
   line = f_in.readline()
  
f_in.close()
f_out.close()