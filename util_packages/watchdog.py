#! /usr/bin/python
import time
import threading
import sys

class WatchDog():
   def __init__(self, timeout):
      self.timeout = timeout
      self.last_ping_time = time.time()

   def ping(self):
      self.last_ping_time = time.time()

   def check(self):
      if time.time() - self.last_ping_time > self.timeout:
         self.last_ping_time = time.time() #reset tick time
         return True
      else:
         return False
         
   def insideMargin(self):
      if time.time() - self.last_ping_time <= self.timeout:
         return True
      else:
         self.last_ping_time = time.time() #reset tick time
         return False


class WatchDogDaemon(threading.Thread):
   def __init__(self, timeout, periodicity, start = True):
      self.wd = WatchDog(timeout)
      self.periodicity = periodicity

      threading.Thread.__init__(self)
      self.daemon = True

      if start == True:
         self.start()

   def ping(self):
      self.wd.ping()

   def run(self):
      print "Starting "
      while(1):
         time.sleep(self.periodicity)

         if not self.wd.insideMargin():
            self.reset()

   def reset(self):
      """to be overriden by client"""
      pass

def reset():
   print 'reset'

def main():
   i = 0
   wdd = WatchDogDaemon(2, 0.5)
   wdd.reset = reset
   try:
      while 1:
         time.sleep(1)
         print 'main_' + str(i)
         i = i+1

         wdd.ping()

   except KeyboardInterrupt:
      raise SystemExit

if __name__ == '__main__':
   main()