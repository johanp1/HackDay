#! /usr/bin/python
import unittest
import luber


class TestComp(unittest.TestCase):

   def setUp(self):
      
      self.c = luber.ComponentWrapper('hal_comp')
      self.c.addPin('out_pin', 'bit', 'out')
      self.c.addPin('in_pin', 'u32', 'in')
      
   def test_init(self):
      self.local_c = luber.ComponentWrapper('local_hal_comp', )
      
      self.assertTrue(self.local_c.hal.name == 'local_hal_comp')
      self.assertTrue(len(self.local_c.pinDict) == 0)
    
   def test_setReady(self):
      self.assertFalse(self.c.hal.readyFlag)
      self.c.setReady()
      self.assertTrue(self.c.hal.readyFlag)
      
   def test_addOutPin(self):
      self.local_c = luber.ComponentWrapper('local_hal_comp')
      
      self.local_c.addPin('local_pin', 'bit', 'out')

      self.assertTrue(len(self.local_c.pinDict) == 1)
      self.assertTrue(self.local_c.pinDict['local_pin'].val == 0)
 
      self.assertTrue(self.local_c.hal['local_pin'] == 0)
      self.assertTrue(self.local_c.hal.pinDict['local_pin'].type == 'HAL_BIT')
      self.assertTrue(self.local_c.hal.pinDict['local_pin'].dir == 'HAL_OUT')   

   def test_addInPin(self):
      self.local_c = luber.ComponentWrapper('local_hal_comp')
      
      self.local_c.addPin('local_pin', 'u32', 'in')

      self.assertTrue(len(self.local_c.pinDict) == 1)
      self.assertTrue(self.local_c.pinDict['local_pin'].val == 0)

      self.assertTrue(self.local_c.hal['local_pin'] == 0)
      self.assertTrue(self.local_c.hal.pinDict['local_pin'].type == 'HAL_U32')
      self.assertTrue(self.local_c.hal.pinDict['local_pin'].dir == 'HAL_IN')   

   def test_updateOutPin(self):
      self.c.setPin('out_pin', 123)
      self.assertTrue(self.c.hal['out_pin'] == 123)

   def test_readPin(self):
      self.c.hal['in_pin'] = 321
      self.c.readPin('in_pin')
      self.assertTrue(self.c.pinDict['in_pin'].val == 321)

if __name__ == '__main__':
   unittest.main()
