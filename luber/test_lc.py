#! /usr/bin/python
import unittest
import luber  
import subprocess
import filecmp
import my_time

class TestComp(unittest.TestCase):
   def timeMock(self):
      return self._time

   def incMockTime(self, t):
      self._time += t

   def setUp(self):
      my_time.getEhocTime = self.timeMock
      self._time = 0
      self.lubeCtrl = luber.LubeControl(3, 0, 3)
      self.incMockTime(0.1)

   def test_init(self):
      self.assertTrue(self.lubeCtrl.totalDistance == 0)
      self.assertTrue(self.lubeCtrl.state == 'OFF')

   def test_addDistance(self):
      self.lubeCtrl.calcDistFromVel(1, 0, 0)
      expected = round(self.lubeCtrl.totalDistance, 1)
      self.assertTrue(expected == 0.1)

      self.incMockTime(0.1)

      self.lubeCtrl.calcDistFromVel(0, 1, 0)
      expected = round(self.lubeCtrl.totalDistance, 1)
      self.assertTrue(expected == 0.2)

      self.incMockTime(0.1)

      self.lubeCtrl.calcDistFromVel(0, 0, 1)
      expected = round(self.lubeCtrl.totalDistance, 1)
      self.assertTrue(expected == 0.3)

   def test_off_to_on(self):
      self.lubeCtrl.calcDistFromVel(10, 10, 9)
      self.lubeCtrl.runStateMachine()
      expected = round(self.lubeCtrl.totalDistance, 1)
      self.assertTrue(expected == 2.9)

      self.incMockTime(0.1)

      self.lubeCtrl.calcDistFromVel(1, 0, 0)
      self.lubeCtrl.runStateMachine()
      expected = round(self.lubeCtrl.totalDistance, 1)
      self.assertTrue(self.lubeCtrl.state == 'ON')
      self.assertTrue(expected == 0)

   def test_on_to_off(self):
      self.lubeCtrl.calcDistFromVel(10, 10, 11)
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
      self.lubeCtrl.calcDistFromVel(10, 10, 11)
      self.lubeCtrl.runStateMachine()
      self.assertTrue(self.lubeCtrl.state == 'ON')

      self.lubeCtrl.setLubeLevelOK(False)

      self.incMockTime(self.lubeCtrl.lubeOnTime + 0.1)
      self.lubeCtrl.runStateMachine()
      self.assertTrue(self.lubeCtrl.state == 'OFF')
      self.assertFalse(self.lubeCtrl.lubeLevelOkOut)

   def test_reset(self):
      self.lubeCtrl.calcDistFromVel(10, 10, 11)
      self.lubeCtrl.runStateMachine()
      self.assertTrue(self.lubeCtrl.state == 'ON')

      self.lubeCtrl.reset()

      self.assertTrue(self.lubeCtrl.state == 'OFF')
      self.assertTrue(self.lubeCtrl.totalDistance == 0)
      

if __name__ == '__main__':
   unittest.main()