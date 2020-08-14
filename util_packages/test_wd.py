#!/usr/bin/python
import unittest
import watchdog
import time
   
class TestWatchDog(unittest.TestCase):
   def timeMock(self):
      return self._time

   def incMockTime(self, t):
      self._time += t

   def setUp(self):
      self.savedTimeMethod = time.time # save time-methos to be restored in restore...
      time.time = self.timeMock        #override time
      self._time = 0

      self.wd = watchdog.WatchDog(10)
      
   def tearDown(self):
      # Restore the time.time function
      time.time = self.savedTimeMethod

   def test_init(self):
      self.assertTrue(self.wd.tickTime == 0)
      self.assertTrue(self.wd.timeout == 10)

   def test_tick(self):
      self.incMockTime(100)
      self.wd.ping()
      self.assertTrue(self.wd.tickTime == 100)

   def test_check(self):
      # check within timeout/margin
      self.incMockTime(10)
      self.assertFalse(self.wd.check())

      # check when timeout/margin expired
      self.incMockTime(1)
      self.assertTrue(self.wd.check())

if __name__ == '__main__':
   unittest.main()