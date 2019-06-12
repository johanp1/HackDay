#! /usr/bin/python

class Serial:

   def __init__(self):
      self.port = 1
      self.baudrate = 9600
      self.parity = 'N'
      self.bytesize = 8
      self.stopbits = 1
      self.xonxoff = False
      self.in_waiting = False
      self.ev_str = ''

   def open(self):
      pass

   def flush(self):
      pass
      
   def read_until(self):
      if self.in_waiting == True:
         self.in_waiting = False
         return self.ev_str.encode('utf-8')
       
   def stub_set_in_waiting(self, f):
      self.in_waiting = f

   def stub_set_read(self, str):
      self.in_waiting = True
      self.ev_str = str