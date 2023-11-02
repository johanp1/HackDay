#! /usr/bin/python
import unittest
import time
import luber

class TestComp(unittest.TestCase):
   def time_mock(self):
      return self._time

   def inc_mock_time(self, t):
      self._time += t

   def setUp(self):
      self.saved_time_method = time.time # save time-methos to be restored in restore...
      time.time = self.time_mock        #override time
      self._time = 0
      self.lubeCtrl = luber.LubeControl(3, 0, 3, 1)
      self.inc_mock_time(0.1)
      
   def tearDown(self):
      # Restore the time.time function
      time.time = self.saved_time_method

   def test_init(self):
      self.assertTrue(self.lubeCtrl.total_distance == 0)
      self.assertTrue(self.lubeCtrl.state == 'OFF')

   def test_addDistance(self):
      self.lubeCtrl.calc_dist_from_vel(1, 0, 0)
      expected = round(self.lubeCtrl.total_distance, 1)
      self.assertTrue(expected == 0.1)

      self.inc_mock_time(0.1)

      self.lubeCtrl.calc_dist_from_vel(0, 1, 0)
      expected = round(self.lubeCtrl.total_distance, 1)
      self.assertTrue(expected == 0.2)

      self.inc_mock_time(0.1)

      self.lubeCtrl.calc_dist_from_vel(0, 0, 1)
      expected = round(self.lubeCtrl.total_distance, 1)
      self.assertTrue(expected == 0.3)

   def test_off_to_on(self):
      self.lubeCtrl.calc_dist_from_vel(10, 10, 9)
      self.lubeCtrl.run_state_machine(False)
      expected = round(self.lubeCtrl.total_distance, 1)
      self.assertTrue(expected == 2.9)
      self.assertTrue(self.lubeCtrl.number_of_lubings == 1)

      self.inc_mock_time(0.1)

      self.lubeCtrl.calc_dist_from_vel(1, 0, 0)
      self.lubeCtrl.run_state_machine(False)
      expected = round(self.lubeCtrl.total_distance, 1)
      self.assertTrue(self.lubeCtrl.state == 'ON')
      self.assertTrue(expected == 0)
      self.assertTrue(self.lubeCtrl.number_of_lubings == 2)

   def test_on_to_off(self):
      self.lubeCtrl.calc_dist_from_vel(10, 10, 11)
      self.lubeCtrl.run_state_machine(False)
      self.assertTrue(self.lubeCtrl.state == 'ON')

      self.inc_mock_time(self.lubeCtrl.lube_on_time)
      self.lubeCtrl.run_state_machine(False)
      self.assertTrue(self.lubeCtrl.state == 'ON')

      self.inc_mock_time(0.1)
      self.lubeCtrl.run_state_machine(False)
      self.assertTrue(self.lubeCtrl.state == 'OFF')
      self.assertTrue(self.lubeCtrl.lube_level_ok)

   def test_low_lube_level(self):
      self.lubeCtrl.calc_dist_from_vel(10, 10, 11)
      self.lubeCtrl.run_state_machine(False)
      self.assertTrue(self.lubeCtrl.state == 'ON')

      self.lubeCtrl.set_lube_level_ok(False)

      self.inc_mock_time(self.lubeCtrl.lube_on_time + 0.1)
      self.lubeCtrl.run_state_machine(False)
      self.assertTrue(self.lubeCtrl.state == 'OFF')
      self.assertFalse(self.lubeCtrl.lube_level_ok)

   def test_reset(self):
      self.lubeCtrl.calc_dist_from_vel(10, 10, 11)
      self.lubeCtrl.run_state_machine(False)
      self.assertTrue(self.lubeCtrl.state == 'ON')

      self.lubeCtrl.reset()

      self.assertTrue(self.lubeCtrl.state == 'OFF')
      self.assertTrue(self.lubeCtrl.total_distance == 0)
      self.assertTrue(self.lubeCtrl.number_of_lubings == 2) # don't reset

   def test_external_request(self):
      self.lubeCtrl.calc_dist_from_vel(0, 0, 0)
      self.lubeCtrl.run_state_machine(False)
      self.assertTrue(self.lubeCtrl.state == 'OFF')

      self.lubeCtrl.run_state_machine(True)
      self.assertTrue(self.lubeCtrl.state == 'ON')

      self.inc_mock_time(self.lubeCtrl.lube_on_time)
      self.lubeCtrl.run_state_machine(False)
      self.assertTrue(self.lubeCtrl.state == 'ON')

      self.inc_mock_time(0.1)
      self.lubeCtrl.run_state_machine(False)
      self.assertTrue(self.lubeCtrl.state == 'OFF')
      self.assertTrue(self.lubeCtrl.lube_level_ok)

if __name__ == '__main__':
   unittest.main()