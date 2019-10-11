#! /usr/bin/python
import unittest
import serial_mpg
import comms  

class TestComp(unittest.TestCase):

   def setUp(self):
      pinDict = {}
      pinDict['apa'] = serial_mpg.Pin('apa_pin', 'u32')
      pinDict['bepa'] = serial_mpg.Pin('bepa_pin', 's32')
      self.c = serial_mpg.ComponentWrapper('hal_comp', pinDict)
      
   def test_init(self):
      self.local_c = serial_mpg.ComponentWrapper('local_hal_comp', {})
      
      self.assertTrue(self.local_c.hal.name == 'local_hal_comp')
      self.assertTrue(len(self.local_c.evToHALPin) == 0)
    
   def test_setReady(self):
      self.assertFalse(self.c.hal.ready_flag)
      self.c.setReady()
      self.assertTrue(self.c.hal.ready_flag)
      
      
   def test_addOnePin(self):
      self.local_c = serial_mpg.ComponentWrapper('local_hal_comp')
      
      self.local_c.addPin('local_ev', 'local_pin', 'u32')

      self.assertTrue(len(self.local_c.evToHALPin) == 1)
      self.assertTrue(self.local_c.evToHALPin['local_ev'].name == 'local_pin')
      self.assertTrue(self.local_c.evToHALPin['local_ev'].val == 0)
      self.assertTrue(self.local_c.evToHALPin['local_ev'].type == 'u32')
      self.assertTrue(self.local_c.hal['local_pin'].val == 0)
      self.assertTrue(self.local_c.hal['local_pin'].type == 'HAL_U32')
         
   def test_noEvents(self):
      self.assertTrue(self.c.hal['apa_pin'].val == 0)
      self.assertTrue(self.c.hal['bepa_pin'].val == 0)
      
      self.c.updateHAL()

      self.assertTrue(self.c.hal['apa_pin'].val == 0)
      self.assertTrue(self.c.hal['bepa_pin'].val == 0)
   
   
   def test_eventHandler(self):
      self.assertTrue(self.c.hal['apa_pin'].val == 0)
      self.assertTrue(self.c.hal['bepa_pin'].val == 0)
      
      self.c.updatePin(comms.event('apa', '12'))
      self.c.updatePin(comms.event('bepa', '321'))
      
      self.c.updateHAL()

      self.assertTrue(self.c.hal['apa_pin'].val == 12)
      self.assertTrue(self.c.hal['bepa_pin'].val == 321)
   
   def test_updateBitTypePin(self):     
      self.c.addPin('bit_ev', 'bit_pin', 'bit')
      self.assertTrue(self.c.evToHALPin['bit_ev'].name == 'bit_pin')
      self.assertTrue(self.c.evToHALPin['bit_ev'].val == 0)
      self.assertTrue(self.c.evToHALPin['bit_ev'].type == 'bit')
      self.assertTrue(self.c.hal['bit_pin'].val == 0)
      self.assertTrue(self.c.hal['bit_pin'].type == 'HAL_BIT')
      
      self.c.updatePin(comms.event('bit_ev', '123'))
      
      self.c.updateHAL()

      self.assertTrue(self.c.hal['bit_pin'].val == 1)
   
   def test_maintainPinValue(self):
      self.c.updatePin(comms.event('apa', '21'))
      self.c.updatePin(comms.event('bepa', '123'))
      
      self.c.updateHAL()

      self.assertTrue(self.c.hal['apa_pin'].val == 21)
      self.assertTrue(self.c.hal['bepa_pin'].val == 123)
      
      self.c.updateHAL()

      self.assertTrue(self.c.hal['apa_pin'].val == 21)
      self.assertTrue(self.c.hal['bepa_pin'].val == 123)
   
   def test_updateWrongEvent(self):
      self.c.updatePin(comms.event('test', '666'))
      
      self.c.updateHAL()
      
      self.assertTrue(self.c.hal['apa_pin'].val == 0)
      self.assertTrue(self.c.hal['bepa_pin'].val == 0)
      
if __name__ == '__main__':
   unittest.main()
