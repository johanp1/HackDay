#! /usr/bin/python
import unittest
import luber


class TestHalAdapter(unittest.TestCase):

   def setUp(self):
      
      self.ha = luber.HalAdapter('hal_comp')
   
      
   def test_init(self):
      self.local_ha = luber.HalAdapter('local_hal_adaptor', )
      
      self.assertTrue(self.local_ha.h.name == 'local_hal_adaptor')
      self.assertTrue(self.local_ha.h.pinDict.has_key('velocity'))
      self.assertTrue(self.local_ha.h.pinDict.has_key('x-vel'))
      self.assertTrue(self.local_ha.h.pinDict.has_key('y-vel'))
      self.assertTrue(self.local_ha.h.pinDict.has_key('z-vel'))
      self.assertTrue(self.local_ha.h.pinDict.has_key('lube-level-ok'))
      self.assertTrue(self.local_ha.h.pinDict.has_key('reset'))
      self.assertTrue(self.local_ha.h.pinDict.has_key('lube-cmd'))
      self.assertTrue(self.local_ha.h.pinDict.has_key('lube-level-alarm'))
      self.assertTrue(self.local_ha.h.pinDict.has_key('accumulated-distance'))

   def test_is_lube_level_ok(self):
      self.ha.h['lube-level-ok'] = 1
      self.assertTrue(self.ha.is_lube_level_ok() == True)

      self.ha.h['lube-level-ok'] = 0
      self.assertTrue(self.ha.is_lube_level_ok() == False)

   def test_is_reset(self):
      self.ha.h['reset'] = 1
      self.assertTrue(self.ha.is_reset() == True)

      self.ha.h['reset'] = 0
      self.assertTrue(self.ha.is_reset() == False)

   def test_get_velocities(self):
      self.ha.h['x-vel'] = 1.23
      self.ha.h['y-vel'] = 4.56
      self.ha.h['z-vel'] = 7.89
      v = self.ha.get_velocities()
      self.assertTrue(v.x == 1.23)
      self.assertTrue(v.y == 4.56)
      self.assertTrue(v.z == 7.89)

   def test_set_lube_on(self):
      self.ha.set_lube_on(0)
      self.assertTrue(self.ha.h['lube-cmd'] == 0)
      self.ha.set_lube_on(1)
      self.assertTrue(self.ha.h['lube-cmd'] == 1)

      #try a "larger then bit" value
      self.ha.set_lube_on(1000)
      self.assertTrue(self.ha.h['lube-cmd'] == 1)

   def test_set_lube_level_alarm(self):
      self.ha.set_lube_level_alarm(0)
      self.assertTrue(self.ha.h['lube-level-alarm'] == 0)
      self.ha.set_lube_level_alarm(1)
      self.assertTrue(self.ha.h['lube-level-alarm'] == 1)

      #try a "larger then bit" value
      self.ha.set_lube_level_alarm(1)
      self.assertTrue(self.ha.h['lube-level-alarm'] == 1)

   def test_set_accumulated_distance(self):
      self.ha.set_accumulated_distance(0)
      self.assertTrue(self.ha.h['accumulated-distance'] == 0)
      self.ha.set_accumulated_distance(100.1)
      self.assertTrue(self.ha.h['accumulated-distance'] == 100.1)

if __name__ == '__main__':
   unittest.main()