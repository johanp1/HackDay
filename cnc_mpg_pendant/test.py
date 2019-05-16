#!/usr/bin/python
import hal, time
import serial

def updatePin(str):
   """parses incomming cmd and update Pin data value accordingly
   input: command string, formated as: '<event>_<number>\n' 
   output: nothing.
   """
   cmd = str.split('_')
   if len(cmd) == 2:
      val = cmd[1] 
      ev = cmd[0]
      
   return cmd[1]


h = hal.component("passthrough")

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


#try:
#   ser.open()
#except serial.SerialException as e:
#   raise SystemExit

try:
   while 1:
   time.sleep(1)
   h[’out’] = h[’in’]
except KeyboardInterrupt:
   raise SystemExit
   
   
#try:
#   while 1:
   
#      while ser.in_waiting:
#            b = ser.read_until() #blocks until '\n' received or timeout
#            out_val = updatePin(b.decode('utf-8'))
            
#   h[’out’] = out_val
#   time.sleep(1)
 
#except KeyboardInterrupt:
#   raise SystemExit