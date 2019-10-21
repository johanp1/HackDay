#!/usr/bin/python
import unittest
import comms
   
class TestComms(unittest.TestCase):
   def _eventHandler(self, ev):
      self.e.append(ev)

   def setUp(self):
      self.s = comms.instrument('/dev/ttyS0', self._eventHandler)
      self.e = []
      
   def test_init(self):
      self.assertTrue(self.s.serial.port == '/dev/ttyS0')
   
   def test_closePort(self):
      self.assertTrue(self.s.portOpened)
      self.s.close()
      self.assertFalse(self.s.portOpened)

   def test_readEvent_noData(self):
      self.s.serial.stub_set_read(['']) #no data in buffer
      
      self.s.readEvents()
      
      self.assertTrue(len(self.e) == 0)
   
   def test_readOneEvent(self):
      self.s.serial.stub_set_read(['jog_10'])
      
      self.s.readEvents()
      
      self.assertTrue(len(self.e) == 1)
      self.assertTrue(self.e[0].ev == 'jog')
      self.assertTrue(self.e[0].val == '10')
      
   def test_readOneBadEvent(self):
      self.s.serial.stub_set_read(['jog10'])
      
      self.s.readEvents()
      
      self.assertTrue(len(self.e) == 0)
    
   def test_readOneBadEvent2(self):
      self.s.serial.stub_set_read(['jog_10_apa'])
      
      self.s.readEvents()
      
      self.assertTrue(len(self.e) == 0)
      
   def test_readOneBadEvent3(self):
      self.s.serial.stub_set_read(['jog_apa'])
      
      self.s.readEvents()
      
      self.assertTrue(len(self.e) == 0)
      
   def test_readTwoEvents(self):
      self.s.serial.stub_set_read(['apa_10', 'bepa_11'])
      
      self.s.readEvents()
      
      self.assertTrue(len(self.e) == 2)
      
      # the subbed serial-module will return the events "last in first out"
      self.assertTrue(self.e[0].ev == 'bepa')
      self.assertTrue(self.e[0].val == '11')
      self.assertTrue(self.e[1].ev == 'apa')
      self.assertTrue(self.e[1].val == '10')

   def test_faildOpenPort(self):
      self.s = comms.instrument('fail', self._eventHandler)
      self.assertFalse(self.s.portOpened)
      
   def test_readFailedPort(self):
      self.s = comms.instrument('fail', self._eventHandler)
      self.s.serial.stub_set_read(['jog_10'])
      
      self.s.readEvents()
      
      self.assertTrue(len(self.e) == 0)  
      
if __name__ == '__main__':
   unittest.main()