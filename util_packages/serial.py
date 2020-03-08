#! /usr/bin/python

class SerialException(Exception):
   pass

class Serial:

   def __init__(self):
      self.port = 1
      self.baudrate = 9600
      self.parity = 'N'
      self.bytesize = 8
      self.stopbits = 1
      self.xonxoff = False
      self.in_waiting = False
      self.msgs = ['']
      self.nbr_msgs = 0
      
   def open(self):
      if self.port == 'fail':
         raise SerialException

   def close(self):
      pass

   def flush(self):
      pass
      
   def read_until(self):
      """ send/return the last sting in msgs array """
      if self.nbr_msgs > 0:
         retStr = self.msgs[self.nbr_msgs-1].encode('utf-8')     
         
         self.nbr_msgs = self.nbr_msgs - 1
         if self.nbr_msgs == 0:
            self.in_waiting = False
         
         return retStr

   def stub_set_read(self, array_of_strings):
      self.nbr_msgs = len(array_of_strings)
      self.msgs = array_of_strings
      
      if self.nbr_msgs > 0:
         self.in_waiting = True