#!/usr/bin/env python
# list available ports with 'python -m serial.tools.list_ports'
import serial
import watchdog

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
   def __init__(self, name = '', data = ''):
      self.name = name
      try:
         if str(data).isascii():
            self.data = str(data)
         else:
            self.data = ''
      except:
         print("data was not a possible to convert to ascii-encoded unicode string")
         self.data = ''

   def __repr__(self):
      return 'msg: ' + self.name + ' val: ' + self.data

   def copy(self, msg):
      self.name = msg.name
      self.data = msg.data

class instrument:
   """rs232 port"""

   def __init__(self, 
                port, 
                msg_handler, 
                watchdog_enabled = False, 
                watchdog_timeout = 2,
                watchdog_periodicity = 0.5):
      self.serial = serial.Serial()
      self.serial.port = port
      self.serial.baudrate = BAUDRATE
      self.serial.parity = PARITY
      self.serial.bytesize = BYTESIZE
      self.serial.stopbits = STOPBITS
      self.serial.xonxoff = False       # disable software flow control
      self.serial.timeout = TIMEOUT
      self.msg_hdlr = msg_handler

      self.watchdog_daemon = watchdog.WatchDogDaemon(watchdog_timeout,
                                                     watchdog_periodicity,
                                                     watchdog_enabled)
      self.watchdog_daemon.reset = self._watchdogClose #register watchdog reset function
      self.closed_by_watchdog = False

      self.open()

   def open(self):
      try:
         self.serial.open()
         #print 'comms::opening port'
      except serial.SerialException:
         print('serial.SerialException caught: unable to open port...')

   def close(self):
      self.serial.close()
      #print 'comms::closing port'

   def dataReady(self):
      if self.is_open():
         return self.serial.in_waiting     
      else:
         return False
         
   def readMessages(self):
      """reads serial port. creates an array of events
      output: array of events: 
      """
      if self.closed_by_watchdog:
         self.closed_by_watchdog = False
         self.open()

      while self.dataReady():
         msg_str = self._read().split('_', 1)

         if msg_str[0] != '':
            self.msg_hdlr(Message(*msg_str))
            self.watchdog_daemon.ping()

   def generateEvent(self, name, data = ''):
      """
      name - is a string
      data - can be any thing possible to serialize into string
      """
      self.writeMessage(Message(name, data))

   def writeMessage(self, m):
      self._write(m.name)

      if  m.data != '':
         self._write('_')
         self._write(m.data)

      self._write('\n')

   def enableWatchdog(self, enable):
      self.watchdog_daemon.setEnabled(enable)

   def is_open(self):
      return self.serial.is_open

   def _write(self, s):
      """
      writes string s to serial port
      string needs to be converted to bytes
      """
      if self.is_open() == True:
         #serial expects data with type <bytes> and not a string
         if isinstance(s, bytes):
            self.serial.write(s)   

         if isinstance(s, str):   
            self.serial.write(s.encode('utf-8', 'ignore'))
         
     
   def _read(self):
      """ returns string read from serial port """
      b = ''
      if self.is_open() == True:
         b = self.serial.read_until() #blocks until '\n' received or timeout
         
      return b.decode('utf-8', 'ignore')        #convert bytes to string

   def _watchdogClose(self):
      self.closed_by_watchdog = True
      self.close()

   def _is_number(self, s):
      """  helper function to evaluate if input text represents an integer or not """
      try:
         int(s)
         return True
      except ValueError:
         return False