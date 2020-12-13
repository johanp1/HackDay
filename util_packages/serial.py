#! /usr/bin/python
import threading
import time

class SerialException(Exception):
   pass

class Serial(threading.Thread):

   def __init__(self, start_deamon = True):
      self.reset()
      threading.Thread.__init__(self)
      self.daemon=True

      if start_deamon == True:
         self.start()

   def run(self):
      while (True):
         try:
            input_str = raw_input()
         except EOFError: 
            raise SystemExit

         if input_str is not None:
            self.stub_set_read([input_str])

         time.sleep(0.1) 

   def reset(self):
      self.port = 1
      self.baudrate = 9600
      self.parity = 'N'
      self.bytesize = 8
      self.stopbits = 1
      self.xonxoff = False
      self.in_waiting = False
      self.msgs = ['']
      self.nbr_msgs = 0
      self.writeBuf = ''

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
         retStr = self.msgs[self.nbr_msgs-1] #.encode('utf-8')     
         
         self.nbr_msgs = self.nbr_msgs - 1
         if self.nbr_msgs == 0:
            self.in_waiting = False
         
         return retStr

   def write(self, b):
      self.writeBuf += (b.decode('utf-8'))

   def stub_set_read(self, array_of_strings):
      self.nbr_msgs = len(array_of_strings)
      self.msgs = array_of_strings
      
      if self.nbr_msgs > 0:
         self.in_waiting = True