#! /usr/bin/python
import unittest
import serialEventHandler as eh

class Observer:
   def __init__(self):
       self.reset()

   def update(self, name, val):
      self.name = name
      self.val = val

   def reset(self):
      self.name = ''
      self.val = 0

class TestComp(unittest.TestCase):

   def setUp(self):
      self.c = eh.HALComponentWrapper('hal_comp')
      self.c.add_pin('apa', 'apa_pin', 'u32')
      self.c.add_pin('bepa', 'bepa_pin', 's32')

   def tearDown(self):
      del self.c

   def test_init(self):
      self.local_c = eh.HALComponentWrapper('local_hal_comp')
      
      self.assertTrue(self.local_c.hal.name == 'local_hal_comp')
      self.assertTrue(len(self.local_c.pin_dict) == 0)
   
   def notify(self, name, val):
      print name + ' has changed to ' + str(val)

   def test_setReady(self):
      self.assertFalse(self.c.hal.readyFlag)
      self.c.setReady()
      self.assertTrue(self.c.hal.readyFlag)
      
   def test_addOutputPin(self):
      self.local_c = eh.HALComponentWrapper('local_hal_comp')
      
      self.local_c.add_pin('local_ev', 'local_pin', 'u32')
      
      self.assertTrue(len(self.local_c.pin_dict) == 1)
      self.assertTrue(self.local_c.pin_dict['local_ev'].name == 'local_pin')
      self.assertTrue(self.local_c.pin_dict['local_ev'].val == 0)
      self.assertTrue(self.local_c.pin_dict['local_ev'].type == 'u32')
      self.assertTrue(self.local_c.pin_dict['local_ev'].__class__.__name__ == 'OutPin')

      self.assertTrue(self.local_c.hal['local_pin'] == 0)
      self.assertTrue(self.local_c.hal.pinDict['local_pin'].type == 'HAL_U32')
      self.assertTrue(self.local_c.hal.pinDict['local_pin'].dir == 'HAL_OUT')
         
   def test_addInputPin(self):
      self.local_c = eh.HALComponentWrapper('local_hal_comp')
      
      self.local_c.add_pin('local_ev', 'local_pin', 'u32', 'in')
      
      self.assertTrue(len(self.local_c.pin_dict) == 1)
      self.assertTrue(self.local_c.pin_dict['local_ev'].name == 'local_pin')
      self.assertTrue(self.local_c.pin_dict['local_ev'].val == 0)
      self.assertTrue(self.local_c.pin_dict['local_ev'].type == 'u32')

      self.assertTrue(self.local_c.hal['local_pin'] == 0)
      self.assertTrue(self.local_c.hal.pinDict['local_pin'].type == 'HAL_U32')
      self.assertTrue(self.local_c.hal.pinDict['local_pin'].dir == 'HAL_IN')

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

   def test_updateInputPin(self):      
      observer = Observer()
      self.c.attach(observer)
      self.c.add_pin('inpin', 'in-pin', 'u32', 'in')

      self.assertTrue(self.c.pin_dict['inpin'].name == 'in-pin')
      self.assertTrue(self.c.pin_dict['inpin'].val == 0)
      self.assertTrue(self.c.pin_dict['inpin'].type == 'u32')
      self.assertTrue(self.c.pin_dict['inpin'].__class__.__name__ == 'InPin')

      self.assertTrue(self.c.hal['in-pin'] == 0)
      self.assertTrue(self.c.hal.pinDict['in-pin'].type == 'HAL_U32')
      self.assertTrue(self.c.hal.pinDict['in-pin'].dir == 'HAL_IN')
      
      #set a new value on the (mocked)hal-pin
      self.c.hal['in-pin'] = 1
      self.c.update_hal()

      #make sure the updated value is propagated to the componentWrapper-instance
      self.assertTrue(self.c.pin_dict['inpin'].val == 1)
      #self.assertTrue(o.name == 'inpin')
      #self.assertTrue(o.val == 1)

   def test_setInputPin(self):
      self.c.add_pin('inpin', 'in-pin', 'u32', 'in')

      self.c.set_pin('inpin', 100)
      self.assertTrue(self.c.pin_dict['inpin'].val == 0)
      self.c.update_hal()
      # nothin changed, only hal can change value for InPin-type
      self.assertTrue(self.c.pin_dict['inpin'].val == 0)
      self.assertTrue(self.c.hal['in-pin'] == 0)
      
   def test_setNonInt(self):
      self.c.set_pin('apa', 'hej')
      self.c.set_pin('bepa', 'jeh')
      
      self.c.update_hal()

      self.assertTrue(self.c.hal['apa_pin'] == 0)
      self.assertTrue(self.c.hal['bepa_pin'] == 0)

   def test_noNotificationIfSameValue(self):
      observer = Observer()

      self.c.add_pin('inpin', 'in-pin', 'u32', 'in')
      self.c.hal['in-pin'] = 1
      self.c.attach(observer)
      self.c.update_hal()
      #make sure the updated value is propagated to the componentWrapper-instance
      self.assertTrue(observer.name == 'inpin')
      self.assertTrue(observer.val == 1)

      # clear observer
      observer.reset()
      
      self.c.update_hal()
      #no update
      self.assertTrue(observer.name == '')
      self.assertTrue(observer.val == 0)


if __name__ == '__main__':
   unittest.main()

#setting input pin
#setting non-int value