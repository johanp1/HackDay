#!/usr/bin/python
import unittest
import comms
   
class TestComms(unittest.TestCase):
   def _messageHandler(self, event):
      self.m.append(event)

   def setUp(self):
      self.s = comms.instrument('/dev/ttyS0', self._messageHandler)
      self.m = []
      
   def test_init(self):
      self.assertTrue(self.s.serial.port == '/dev/ttyS0')
   
   def test_closePort(self):
      self.assertTrue(self.s.is_open())
      self.s.close()
      self.assertFalse(self.s.is_open())
   
   def test_readMessage_noData(self):
      self.s.serial.stub_set_read([b'']) #no data in buffer
      
      self.s.readMessages()
      
      self.assertTrue(len(self.m) == 0)
   
   def test_readOneMessageWithPayload(self):
      self.s.serial.stub_set_read([b'jog_10'])
      
      self.s.readMessages()
      
      self.assertTrue(len(self.m) == 1)
      self.assertTrue(self.m[0].name == 'jog')
      self.assertTrue(self.m[0].data == '10')
   
   def test_readOneMessageNoPayload(self):
      self.s.serial.stub_set_read([b'goj'])
      
      self.s.readMessages()
      
      self.assertTrue(len(self.m) == 1)
      self.assertTrue(self.m[0].name == 'goj')
      self.assertTrue(self.m[0].data == '')
  
   def test_readBadMessage(self):
      self.s.serial.stub_set_read([b'jog_'])
      
      self.s.readMessages()
      
      self.assertTrue(len(self.m) == 1)
      self.assertTrue(self.m[0].name == 'jog')
      self.assertTrue(self.m[0].data == '')
   
   def test_readOneBadMessage4(self):
      #data that can not be decoded...
      self.s.serial.stub_set_read([b'\xf0'])

      self.s.readMessages()
      
      self.assertTrue(len(self.m) == 0)
   
   def test_readTwoMessages(self):
      self.s.serial.stub_set_read([b'apa_10', b'bepa_11'])
      
      self.s.readMessages()
      
      self.assertTrue(len(self.m) == 2)
      
      # the subbed serial-module will return the messages "last in first out"
      self.assertTrue(self.m[0].name == 'bepa')
      self.assertTrue(self.m[0].data == '11')
      self.assertTrue(self.m[1].name == 'apa')
      self.assertTrue(self.m[1].data == '10')

   def test_faildOpenPort(self):
      self.s = comms.instrument('fail', self._messageHandler)
      self.assertFalse(self.s.is_open())
      
   def test_readFailedPort(self):
      self.s = comms.instrument('fail', self._messageHandler)
      self.s.serial.stub_set_read([b'jog_10'])
      
      self.s.readMessages()
      
      self.assertTrue(len(self.m) == 0)  
 
   def test_writeMessage(self):
      self.s.writeMessage(comms.Message('apa', '123'))
      self.assertTrue(self.s.serial.writeBuf == b'apa_123\n')

   def test_writeMessageNoPayload(self):
      self.s.writeMessage(comms.Message('bepa'))
      self.assertTrue(self.s.serial.writeBuf == b'bepa\n')

   def test_writeMessagePortClosed(self):
      self.s.close()
      self.s.writeMessage(comms.Message('apa', '123'))
      self.assertTrue(self.s.serial.writeBuf == b'')

   def test_generateEvent(self):
      self.s.generateEvent('apa', '129')
      self.assertTrue(self.s.serial.writeBuf == b'apa_129\n')

   def test_generateEventInt(self):
      self.s.generateEvent('apa', 129)
      self.assertTrue(self.s.serial.writeBuf == b'apa_129\n')

   def test_generateEventFloat(self):
      self.s.generateEvent('apa', 0.01)
      self.assertTrue(self.s.serial.writeBuf == b'apa_0.01\n')

   def test_generateEventInvalid(self):
      """
      s='\x8f' 
      s.encode('ascii') 
      Traceback (most recent call last):
         File "<stdin>", line 1, in <module>
      UnicodeEncodeError: 'ascii' codec can't encode character '\x8f' in position 0: ordinal not in range(128)
      s.encode('utf-8') 
      b'\xc2\x8f'
      """
      self.s.generateEvent('apa', '\x8f')
      self.assertTrue(self.s.serial.writeBuf == b'apa\n')

   def test_generateEventNoPayload(self):
      self.s.generateEvent('bepa')
      self.assertTrue(self.s.serial.writeBuf == b'bepa\n')

if __name__ == '__main__':
   unittest.main()