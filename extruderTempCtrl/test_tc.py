#! /usr/bin/python
import unittest
import hal_exruder_temp_ctrl as tempCtrler

class TestComp(unittest.TestCase):
   def setUp(self):
      
      self._time = 0
      self.tc = tempCtrler.TempControllerFacade('dummy')

def test_init(self):
   self.assertTrue(self.tc.currTemp == 100)