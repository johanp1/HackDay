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


class Event:
   """'container for events. keeps two strings <event> and <value>"""
   def __init__(self, event, value):
      self.ev = event
      self.val = value
      
   def __repr__(self):
      return 'ev: ' + self.ev + ' val: ' + self.val

class instrument:
   """rs232 port"""

   def __init__(self, port, event_handler):
      self.serial = serial.Serial()
      self.serial.port = port
      self.serial.baudrate = BAUDRATE
      self.serial.parity = PARITY
      self.serial.bytesize = BYTESIZE
      self.serial.stopbits = STOPBITS
      self.serial.xonxoff = False       # disable software flow control
      self.serial.timeout = TIMEOUT
      self.portOpened = False
      self.ev_hdlr = event_handler
      
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
         
   def readEvents(self):
      """reads serial port. creates an array of events
      output: array of events: 
      """
      while self.dataReady():
         ev_str = self._read().split('_')

         if len(ev_str) == 2 and self._is_number(ev_str[1]):
            self.ev_hdlr(Event(ev_str[0], ev_str[1]))
      
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