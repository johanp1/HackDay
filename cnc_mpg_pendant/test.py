#!/usr/bin/python
import unittest
import comms

class TestComms(unittest.TestCase):
   def setUp(self):
      self.s = comms.instrument('/dev/ttyS0')
      
   def test_init(self):
      self.assertTrue(self.s.serial.port == '/dev/ttyS0')
      
   def test_dataReady_true(self):
      self.s.serial.stub_set_in_waiting(True)
      self.assertTrue(self.s.dataReady())
      
   def test_dataReady_false(self):
      self.s.serial.stub_set_in_waiting(False)
      self.assertFalse(self.s.dataReady())
   
   def test_readEvent_noData(self):
      self.s.serial.stub_set_in_waiting(False)
      e = self.s.readEvents()
      self.assertTrue(len(e) == 0)
   
   def test_readOneEvent(self):
      self.s.serial.stub_set_read('jog_10')
      e = self.s.readEvents()
      self.assertTrue(len(e) == 1)
      self.assertTrue(e[0].ev == 'jog')
      self.assertTrue(e[0].val == '10')
      
   def test_readOneBadEvent(self):
      self.s.serial.stub_set_read('jog10')
      e = self.s.readEvents()
      self.assertTrue(len(e) == 0)
    
   def test_readOneBadEvent2(self):
      self.s.serial.stub_set_read('jog_10_apa')
      e = self.s.readEvents()
      self.assertTrue(len(e) == 0)
      
   def test_readOneBadEvent3(self):
      self.s.serial.stub_set_read('jog_apa')
      e = self.s.readEvents()
      self.assertTrue(len(e) == 0)
      
   def test_readTwoEvents(self):
      pass
      
if __name__ == '__main__':
   unittest.main()