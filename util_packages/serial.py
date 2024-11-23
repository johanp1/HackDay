#! /usr/bin/python
import threading
import time

class SerialException(Exception):
   pass

class Serial(threading.Thread):

   def __init__(self, start_deamon = False):
      self.port = 1
      self.baudrate = 9600
      self.parity = 'N'
      self.bytesize = 8
      self.stopbits = 1
      self.xonxoff = False
      self.in_waiting = False
      self.is_open = False
      
      self.msgs = [b''] # array of bytes
      self.nbr_msgs = 0
      self.writeBuf = b''

      threading.Thread.__init__(self)
      self.daemon=True

      if start_deamon == True:
         self.start()

   def run(self):
      while (True):
         try:
            input_str = input()
         except EOFError: 
            raise SystemExit

         if input_str is not None:
            self.stub_set_read([input_str])

         time.sleep(0.1) 

   def reset(self):
      #self.port = 1
      #self.baudrate = 9600
      #self.parity = 'N'
      #self.bytesize = 8
      #self.stopbits = 1
      #self.xonxoff = False
      self.in_waiting = False
      self.msgs = [b''] # array of bytes
      self.nbr_msgs = 0
      self.writeBuf = b'' #write() stores it's values here
      #self.is_open = False

   def open(self):
      self.is_open = True
      
      if self.port == 'fail':
         self.is_open = False
         raise SerialException

   def close(self):
      self.is_open = False

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
      """ 
      b - data to send, dataype bytes

      Unicode strings must be encoded (e.g. 'hello'.encode('utf-8')
      """
      # make sure b is of datatype bytes
      if isinstance(b, bytes):
         self.writeBuf += b
      else:
         raise Exception("input must be bytes")

   def stub_set_read(self, array_of_bytes):
      self.nbr_msgs = len(array_of_bytes)
      self.msgs = array_of_bytes
      
      if self.nbr_msgs > 0:
         self.in_waiting = True