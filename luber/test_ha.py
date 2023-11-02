#! /usr/bin/python
import unittest
import luber


class TestHalAdapter(unittest.TestCase):

   def setUp(self):
      
      self.ha = luber.HalAdapter('hal_comp')
   
      
   def test_init(self):
      local_ha = luber.HalAdapter('local_hal_adaptor', )
      
      self.assertTrue(local_ha.h.name == 'local_hal_adaptor')
      self.assertTrue('x-vel' in local_ha.h.pinDict)
      self.assertTrue('y-vel' in local_ha.h.pinDict)
      self.assertTrue('z-vel' in local_ha.h.pinDict)
      self.assertTrue('lube-level-ok' in local_ha.h.pinDict)
      self.assertTrue('reset' in local_ha.h.pinDict)
      self.assertTrue('lube-level-alarm' in local_ha.h.pinDict)
      self.assertTrue('accumulated-distance' in local_ha.h.pinDict)
      self.assertTrue('lube-ext-req' in local_ha.h.pinDict)
      
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

   def test_is_external_request(self):
      self.ha.h['lube-ext-req'] = 1
      self.assertTrue(self.ha.is_lube_ext_req() == True)

      self.ha.h['lube-ext-req'] = 0
      self.assertTrue(self.ha.is_lube_ext_req() == False)


if __name__ == '__main__':
   unittest.main()