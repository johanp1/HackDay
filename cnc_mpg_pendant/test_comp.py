#! /usr/bin/python
import unittest
import pendant_srv
import comms  

class TestComp(unittest.TestCase):

   def setUp(self):
      self.c = pendant_srv.ComponentWrapper()
      
   def test_init(self):
      self.assertTrue(len(self.c.evToHALPin) == 0)
 
   def test_addOnePin(self):
      self.c.addPin('apa', 'apa_pin', 'u32')
      self.assertTrue(len(self.c.evToHALPin) == 1)
      self.assertTrue(self.c.evToHALPin['apa'].name == 'apa_pin')
      self.assertTrue(self.c.evToHALPin['apa'].val == 0)
      self.assertTrue(self.c.evToHALPin['apa'].type == 'u32')

 
   def test_updatePin(self):
      e = comms.event('apa', '12')
      