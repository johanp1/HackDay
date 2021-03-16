#! /usr/bin/python
import unittest
import serialEventHandler as eh

class TestComp(unittest.TestCase):

   def setUp(self):
      self.c = eh.ComponentWrapper('hal_comp')
      self.c.add_pin('apa', 'apa_pin', 'u32')
      self.c.add_pin('bepa', 'bepa_pin', 's32')

   def tearDown(self):
      del self.c

   def test_init(self):
      self.local_c = eh.ComponentWrapper('local_hal_comp')
      
      self.assertTrue(self.local_c.hal.name == 'local_hal_comp')
      self.assertTrue(len(self.local_c.pin_dict) == 0)
    
   def test_setReady(self):
      self.assertFalse(self.c.hal.readyFlag)
      self.c.setReady()
      self.assertTrue(self.c.hal.readyFlag)
      
   def test_addOnePin(self):
      self.local_c = eh.ComponentWrapper('local_hal_comp')
      
      self.local_c.add_pin('local_ev', 'local_pin', 'u32')
      
      self.assertTrue(len(self.local_c.pin_dict) == 1)
      self.assertTrue(self.local_c.pin_dict['local_ev'].name == 'local_pin')
      self.assertTrue(self.local_c.pin_dict['local_ev'].val == 0)
      self.assertTrue(self.local_c.pin_dict['local_ev'].type == 'u32')
      self.assertTrue(self.local_c.hal['local_pin'] == 0)
      self.assertTrue(self.local_c.hal.pinDict['local_pin'].type == 'HAL_U32')
         
   def test_noEvents(self):
      self.assertTrue(self.c.hal['apa_pin'] == 0)
      self.assertTrue(self.c.hal['bepa_pin'] == 0)
      
      self.c.update_hal()

      self.assertTrue(self.c.hal['apa_pin'] == 0)
      self.assertTrue(self.c.hal['bepa_pin'] == 0)
   
   
   def test_eventHandler(self):
      self.assertTrue(self.c.hal['apa_pin'] == 0)
      self.assertTrue(self.c.hal['bepa_pin'] == 0)
      
      self.c.set_pin('apa', '12')
      self.c.set_pin('bepa', '321')
      
      self.c.update_hal()

      self.assertTrue(self.c.hal['apa_pin'] == 12)
      self.assertTrue(self.c.hal['bepa_pin'] == 321)
   
   def test_updateBitTypePin(self):     
      self.c.add_pin('bit_ev', 'bit_pin', 'bit')
      self.assertTrue(self.c.pin_dict['bit_ev'].name == 'bit_pin')
      self.assertTrue(self.c.pin_dict['bit_ev'].val == 0)
      self.assertTrue(self.c.pin_dict['bit_ev'].type == 'bit')
      self.assertTrue(self.c.hal['bit_pin'] == 0)
      self.assertTrue(self.c.hal.pinDict['bit_pin'].type == 'HAL_BIT')
      
      self.c.set_pin('bit_ev', '123')
      
      self.c.update_hal()

      self.assertTrue(self.c.hal['bit_pin'] == 1)
   
   def test_maintainPinValue(self):
      self.c.set_pin('apa', '21')
      self.c.set_pin('bepa', '123')
      
      self.c.update_hal()

      self.assertTrue(self.c.hal['apa_pin'] == 21)
      self.assertTrue(self.c.hal['bepa_pin'] == 123)
      
      self.c.update_hal()

      self.assertTrue(self.c.hal['apa_pin'] == 21)
      self.assertTrue(self.c.hal['bepa_pin'] == 123)
   
   def test_updateWrongEvent(self):
      self.c.set_pin('test', '666')
      
      self.c.update_hal()
      
      self.assertTrue(self.c.hal['apa_pin'] == 0)
      self.assertTrue(self.c.hal['bepa_pin'] == 0)

   def test_getItem(self):
      self.c.set_pin('apa', '21')
      self.assertTrue(self.c['apa'] == 21)

   def test_setItem(self):
      self.c['bepa'] = 21
      self.assertTrue(self.c['bepa'] == 21)

if __name__ == '__main__':
   unittest.main()
