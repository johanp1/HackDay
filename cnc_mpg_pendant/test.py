#!/usr/bin/python
import unittest
import comms
#import pendant_srv
#target = __import__("pendant_srv.py")
#is_number = target.is_number

#import hal
#import time
#import serial
#import getopt

class TestBasic(unittest.TestCase):
   def setUp(self):
      pass
      
   def test_int(self):
      #self.assertTrue(pendant_srv.is_number(6))
      array = []
      array.extend('1')
      
      print array
      self.assertFalse(0)
      
if __name__ == '__main__':
   unittest.main()