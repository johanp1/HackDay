#!/usr/bin/python
import unittest
import comms
   
class TestComms(unittest.TestCase):
   def _messageHandler(self, msg):
      self.m.append(msg)

   def setUp(self):
      self.s = comms.instrument('/dev/ttyS0', self._messageHandler)
      self.m = []
      
   def test_init(self):
      self.assertTrue(self.s.serial.port == '/dev/ttyS0')
   
   def test_closePort(self):
      self.assertTrue(self.s.portOpened)
      self.s.close()
      self.assertFalse(self.s.portOpened)

   def test_readMessage_noData(self):
      self.s.serial.stub_set_read(['']) #no data in buffer
      
      self.s.readMessages()
      
      self.assertTrue(len(self.m) == 0)
   
   def test_readOneMessage(self):
      self.s.serial.stub_set_read(['jog_10'])
      
      self.s.readMessages()
      
      self.assertTrue(len(self.m) == 1)
      self.assertTrue(self.m[0].msg == 'jog')
      self.assertTrue(self.m[0].val == '10')
      
   def test_readOneBadMessage(self):
      self.s.serial.stub_set_read(['jog10'])
      
      self.s.readMessages()
      
      self.assertTrue(len(self.m) == 0)
    
   def test_readOneBadMessage2(self):
      self.s.serial.stub_set_read(['jog_10_apa'])
      
      self.s.readMessages()
      
      self.assertTrue(len(self.m) == 0)
      
   def test_readOneBadMessage3(self):
      self.s.serial.stub_set_read(['jog_apa'])

      self.s.readMessages()
      
      self.assertTrue(len(self.m) == 0)
      
   def test_readOneBadMessage4(self):
      #data that can not be decoded...
      self.s.serial.stub_set_read([b'\xf0'])

      self.s.readMessages()
      
      self.assertTrue(len(self.m) == 0)

   def test_readTwoMessages(self):
      self.s.serial.stub_set_read(['apa_10', 'bepa_11'])
      
      self.s.readMessages()
      
      self.assertTrue(len(self.m) == 2)
      
      # the subbed serial-module will return the messages "last in first out"
      self.assertTrue(self.m[0].msg == 'bepa')
      self.assertTrue(self.m[0].val == '11')
      self.assertTrue(self.m[1].msg == 'apa')
      self.assertTrue(self.m[1].val == '10')

   def test_faildOpenPort(self):
      self.s = comms.instrument('fail', self._messageHandler)
      self.assertFalse(self.s.portOpened)
      
   def test_readFailedPort(self):
      self.s = comms.instrument('fail', self._messageHandler)
      self.s.serial.stub_set_read(['jog_10'])
      
      self.s.readMessages()
      
      self.assertTrue(len(self.m) == 0)  
      
   def test_writeMessage(self):
      self.s.writeMessage(comms.Message('apa', '123'))
      self.assertTrue(self.s.serial.writeBuf == 'apa123\n')

   def test_writeMessagePortClosed(self):
      self.s.close()
      self.s.writeMessage(comms.Message('apa', '123'))
      self.assertTrue(self.s.serial.writeBuf == '')

if __name__ == '__main__':
   unittest.main()