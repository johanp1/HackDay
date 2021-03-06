#! /usr/bin/python
import unittest
import luber  
import time

class TestComp(unittest.TestCase):
   def timeMock(self):
      return self._time

   def incMockTime(self, t):
      self._time += t

   def setUp(self):
      self.savedTimeMethod = time.time # save time-methos to be restored in restore...
      time.time = self.timeMock        #override time
      self._time = 0
      self.lubeCtrl = luber.LubeControl(3, 0, 3, 1)
      self.incMockTime(0.1)
      
   def tearDown(self):
      # Restore the time.time function
      time.time = self.savedTimeMethod

   def test_init(self):
      self.assertTrue(self.lubeCtrl.total_distance == 0)
      self.assertTrue(self.lubeCtrl.state == 'OFF')

   def test_addDistance(self):
      self.lubeCtrl.calc_dist_from_vel(1, 0, 0)
      expected = round(self.lubeCtrl.total_distance, 1)
      self.assertTrue(expected == 0.1)

      self.incMockTime(0.1)

      self.lubeCtrl.calc_dist_from_vel(0, 1, 0)
      expected = round(self.lubeCtrl.total_distance, 1)
      self.assertTrue(expected == 0.2)

      self.incMockTime(0.1)

      self.lubeCtrl.calc_dist_from_vel(0, 0, 1)
      expected = round(self.lubeCtrl.total_distance, 1)
      self.assertTrue(expected == 0.3)

   def test_off_to_on(self):
      self.lubeCtrl.calc_dist_from_vel(10, 10, 9)
      self.lubeCtrl.runStateMachine()
      expected = round(self.lubeCtrl.total_distance, 1)
      self.assertTrue(expected == 2.9)
      self.assertTrue(self.lubeCtrl.numberOfLubings == 1)

      self.incMockTime(0.1)

      self.lubeCtrl.calc_dist_from_vel(1, 0, 0)
      self.lubeCtrl.runStateMachine()
      expected = round(self.lubeCtrl.total_distance, 1)
      self.assertTrue(self.lubeCtrl.state == 'ON')
      self.assertTrue(expected == 0)
      self.assertTrue(self.lubeCtrl.numberOfLubings == 2)

   def test_on_to_off(self):
      self.lubeCtrl.calc_dist_from_vel(10, 10, 11)
      self.lubeCtrl.runStateMachine()
      self.assertTrue(self.lubeCtrl.state == 'ON')

      self.incMockTime(self.lubeCtrl.lubeOnTime)
      self.lubeCtrl.runStateMachine()
      self.assertTrue(self.lubeCtrl.state == 'ON')

      self.incMockTime(0.1)
      self.lubeCtrl.runStateMachine()
      self.assertTrue(self.lubeCtrl.state == 'OFF')
      self.assertTrue(self.lubeCtrl.lubeLevelOkOut)

   def test_low_lube_level(self):
      self.lubeCtrl.calc_dist_from_vel(10, 10, 11)
      self.lubeCtrl.runStateMachine()
      self.assertTrue(self.lubeCtrl.state == 'ON')

      self.lubeCtrl.setLubeLevelOK(False)

      self.incMockTime(self.lubeCtrl.lubeOnTime + 0.1)
      self.lubeCtrl.runStateMachine()
      self.assertTrue(self.lubeCtrl.state == 'OFF')
      self.assertFalse(self.lubeCtrl.lubeLevelOkOut)

   def test_reset(self):
      self.lubeCtrl.calc_dist_from_vel(10, 10, 11)
      self.lubeCtrl.runStateMachine()
      self.assertTrue(self.lubeCtrl.state == 'ON')

      self.lubeCtrl.reset()

      self.assertTrue(self.lubeCtrl.state == 'OFF')
      self.assertTrue(self.lubeCtrl.total_distance == 0)
      self.assertTrue(self.lubeCtrl.numberOfLubings == 2) # don't reset

if __name__ == '__main__':
   unittest.main()