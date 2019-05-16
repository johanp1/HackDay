#!/usr/bin/python
import hal
import time
import serial

def updatePin(str):
   """parses incomming cmd and update Pin data value accordingly
   input: command string, formated as: '<event>_<number>\n' 
   output: nothing.
   """
   val = 0
   cmd = str.split('_')
   if len(cmd) == 2:
      if is_number(cmd[1]):
         val = int(cmd[1]) 
      
   return val

def is_number(s):
    try:
        int(s)
        return True
    except ValueError:
        return False

h = hal.component("test")

h.newpin("in", hal.HAL_FLOAT, hal.HAL_IN)
h.newpin("out", hal.HAL_FLOAT, hal.HAL_OUT)

h.ready()


### open serial port
# list available ports with 'python -m serial.tools.list_ports'
ser = serial.Serial()
ser.port = '/dev/ttyACM0'
ser.baudrate = 9600
ser.parity = 'N'
ser.bytesize = 8
ser.stopbits = 1
ser.xonxoff = False       # disable software flow control
#ser.rtscts = False       # disable hardware (RTS/CTS) flow control
#ser.dsrdtr = False       # disable hardware (DSR/DTR) flow control
#ser.writeTimeout = 2     # timeout for write
ser.timeout = 1           # 1 sec timeout

try:
   ser.open()
except serial.SerialException as e:
   raise SystemExit

out_val = 0
try:
   while 1:
      while ser.in_waiting:
            b = ser.read_until() #blocks until '\n' received or timeout
            out_val = updatePin(b.decode('utf-8'))
            #print b
      h['out'] = out_val
      time.sleep(1)
 
except KeyboardInterrupt:
   raise SystemExit
