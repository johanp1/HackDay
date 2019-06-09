#! /usr/bin/python

class Serial:

   port = 1
   baudrate = 9600
   parity = 'N'
   bytesize = 8
   stopbits = 1
   xonxoff = False
   in_waiting = 1

   def open(self):
      pass

   def flush(self):
      pass
      
   def read_until(self):
      self.in_waiting = 0
      return 'jog_10'.encode('utf-8')
