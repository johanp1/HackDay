#! /usr/bin/python
import unittest
import luber  
import subprocess
import filecmp


class TestComp(unittest.TestCase):

   def setUp(self):
      self._time = 0
      self.lubeCtrl = luber.LubeControl(1, 2, 3, 0, 3, 0)

   def test_init(self):
      self.assertTrue(self.lubeCtrl.totalDistance == 0)
      self.assertTrue(self.lubeCtrl.state == 'OFF')

   def test_addDistance(self):
      self.lubeCtrl.calcDistFromVel(1, 0, 0, 0.1)
      expected = round(self.lubeCtrl.totalDistance, 1)
      self.assertTrue(expected == 0.1)

      self.lubeCtrl.calcDistFromVel(0, 1, 0, 0.2)
      expected = round(self.lubeCtrl.totalDistance, 1)
      self.assertTrue(expected == 0.2)

      self.lubeCtrl.calcDistFromVel(0, 0, 1, 0.3)
      expected = round(self.lubeCtrl.totalDistance, 1)
      self.assertTrue(expected == 0.3)

   def test_gotot_on(self):
      self.lubeCtrl.calcDistFromVel(10, 10, 9, 0.1)
      self.lubeCtrl.runStateMachine()
      expected = round(self.lubeCtrl.totalDistance, 1)
      self.assertTrue(expected == 2.9)

      self.lubeCtrl.calcDistFromVel(1, 0, 0, 0.2)
      self.lubeCtrl.runStateMachine()
      expected = round(self.lubeCtrl.totalDistance, 1)
      self.assertTrue(self.lubeCtrl.state == 'ON')
      self.assertTrue(expected == 0)

if __name__ == '__main__':
   unittest.main()