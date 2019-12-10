#! /usr/bin/python
import unittest
import serial_mpg  

class TestEventHandler(unittest.TestCase):

   def setUp(self):
      self.eh = serial_mpg.EventHandler()
      
   def test_init(self):
      self.eh.handleEvent(Event())