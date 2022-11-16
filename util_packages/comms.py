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
         self.data = str(data).encode('ascii') #serialize, filter strange characters
      except:
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
      self.portOpened = False
      self.msg_hdlr = msg_handler

      self.watchdog_daemon = watchdog.WatchDogDaemon(watchdog_timeout,
                                                     watchdog_timeout,
                                                     watchdog_enabled)
      self.watchdog_daemon.reset = self._watchdogClose #register watchdog reset function
      self.closed_by_watchdog = False

      self.open()

   def open(self):
      try:
         self.serial.open()
         self.portOpened = True
         print 'comms::opening port'
      except serial.SerialException:
         self.portOpened = False
         print 'unable to open port...'

   def close(self):
      self.serial.close()
      self.portOpened = False
      print 'comms::closeing port'

   def dataReady(self):
      if self.portOpened:
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
      self.writeMessage(Message(name, data))

   def writeMessage(self, m):
      self._write(m.name)

      if  m.data != '':
         self._write('_')
         self._write(m.data)

      self._write('\n')

   def enableWatchdog(self, enable):
      self.watchdog_daemon.setEnabled(enable)

   def _write(self, s):
      if self.portOpened == True:
         #serial expects a byte-array and not a string
         self.serial.write(''.join(s).encode('utf-8', 'ignore'))
         
     
   def _read(self):
      """ returns string read from serial port """
      b = ''
      if self.portOpened == True:
         b = self.serial.read_until() #blocks until '\n' received or timeout
         
      return b.decode('utf-8', 'ignore')        #convert byte array to string

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