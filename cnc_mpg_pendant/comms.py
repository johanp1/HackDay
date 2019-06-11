#!/usr/bin/env python

import serial



## Default values ##
BAUDRATE = 9600
"""Default value for the baudrate in Baud (int)."""

PARITY   = 'N' #serial.PARITY_NONE
"""Default value for the parity. See the pySerial module for documentation. Defaults to serial.PARITY_NONE"""

BYTESIZE = 8
"""Default value for the bytesize (int)."""

STOPBITS = 1
"""Default value for the number of stopbits (int)."""

TIMEOUT  = 0.05
"""Default value for the timeout value in seconds (float)."""

CLOSE_PORT_AFTER_EACH_CALL = False
"""Default value for port closure setting."""


### open serial port
# list available ports with 'python -m serial.tools.list_ports'

class event:

   def __init__(self, event, value):
      self.ev = event
      self.val = value
      
   def __repr__(self):
      return 'ev: ' + self.ev + ' val: ' + self.val

class instrument:
   """rs232 port"""

   def __init__(self, port):
      self.serial = serial.Serial()
      self.serial.port = port
      self.serial.baudrate = BAUDRATE
      self.serial.parity = PARITY
      self.serial.bytesize = BYTESIZE
      self.serial.stopbits = STOPBITS
      self.serial.xonxoff = False       # disable software flow control
      self.serial.timeout = TIMEOUT
      
      try:
         self.serial.open()
         self.portOpened = True
      except serial.SerialException as e:
         self.portOpened = False
         sys.stderr.write('{} {}\n'.format(ser.name, e))
         #sys.stderr.write('Could not open serial port {}: {}\n'.format(ser.name, e))
         subprocess.call("echo available ports:", shell=True) 
         subprocess.call("python -m serial.tools.list_ports", shell=True) 
         
   def dataReady(self):
      return self.serial.in_waiting     

   def readEvents(self):
      """reads serial port. creates an array of events
      input: command string, formated as: '<event>_<number>\n' 
      output: nothing.
      """
      ret = []
      while self.dataReady():
         ev_str = self._read().split('_')

         if len(ev_str) == 2:
            ret.append(event(ev_str[0], ev_str[1]))

      return ret     
      
   def _read(self):
      """ returns string read from serial port """
      b = ''
      if self.portOpened == True:
         b = self.serial.read_until() #blocks until '\n' received or timeout
         
      return b.decode('utf-8')
      
   