#!/usr/bin/env python
# list available ports with 'python -m serial.tools.list_ports'
import serial

## Default values ##
BAUDRATE = 38400
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


class Message:
   """'container for messages. keeps two strings <message> and <value>"""
   def __init__(self, message, value):
      self.msg = message
      self.val = value
      
   def __repr__(self):
      return 'msg: ' + self.msg + ' val: ' + self.val

class instrument:
   """rs232 port"""

   def __init__(self, port, msg_handler):
      self.serial = serial.Serial()
      self.serial.port = port
      self.serial.baudrate = BAUDRATE
      self.serial.parity = PARITY
      self.serial.bytesize = BYTESIZE
      self.serial.stopbits = STOPBITS
      self.serial.xonxoff = False       # disable software flow control
      self.serial.timeout = TIMEOUT
      self.portOpened = False
      self.msg_hdlr = msg_handler
      
      self.open()

   def open(self):
      try:
         self.serial.open()
         self.portOpened = True
      except serial.SerialException:
         self.portOpened = False

   def close(self):
      if self.portOpened == True:
         self.serial.close()
         self.portOpened = False

   def dataReady(self):
      if self.portOpened:
         return self.serial.in_waiting     
      else:
         return False
         
   def readMessages(self):
      """reads serial port. creates an array of events
      output: array of events: 
      """
      while self.dataReady():
         msg_str = self._read().split('_')

         if len(msg_str) == 2 and self._is_number(msg_str[1]):
            self.msg_hdlr(Message(msg_str[0], msg_str[1]))

   def writeMessage(self, m):
      self._write(m.msg + m.val + '\n')

   def _write(self, str):
      if self.portOpened == True:
         #serial expects a byte-array and not a string
         self.serial.write(''.join(str).encode('utf-8'))
     
   def _read(self):
      """ returns string read from serial port """
      b = ''
      if self.portOpened == True:
         b = self.serial.read_until() #blocks until '\n' received or timeout
         
      return b.decode('utf-8')        #convert byte array to string
      
   def _is_number(self, s):
      """  helper function to evaluate if input text represents an integer or not """
      try:
         int(s)
         return True
      except ValueError:
         return False