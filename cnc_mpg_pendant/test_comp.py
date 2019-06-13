#! /usr/bin/python
import unittest
import pendant_srv
import comms  

class TestComp(unittest.TestCase):

   def setUp(self):
      self.c = pendant_srv.ComponentWrapper()
      
   def test_init(self):
      self.assertTrue(len(self.c.evToHALPin) == 0)
   
   