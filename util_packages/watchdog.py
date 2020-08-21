#! /usr/bin/python
import time
import threading
import sys

class WatchDog():
   def __init__(self, timeout):
      self.timeout = timeout
      self.tickTime = time.time()

   def ping(self):
      self.tickTime = time.time()

   def check(self):
      if time.time() - self.tickTime > self.timeout:
         self.tickTime = time.time() #reset tick time
         return True
      else:
         return False
         
   def insideMargin(self):
      if time.time() - self.tickTime <= self.timeout:
         return True
      else:
         self.tickTime = time.time() #reset tick time
         return False


class WatchDogDaeomn(threading.Thread):
   def __init__(self, timeout, periodicity):
      self.wd = WatchDog(timeout)
      self.periodicity = periodicity

      threading.Thread.__init__(self)
      self.daemon = True
      self.start()

      self.i = 0

   def ping(self):
      self.wd.ping()

   def run(self):
      print "Starting "
      while(1):
         print 'daemon_' + str(self.i)
         self.i = self.i + 1
         time.sleep(self.periodicity)

         if not self.wd.insideMargin():
            self.reset()
         #if self.wd.check():
         #   self.reset()

   def reset(self):
      """to be overriden by client"""
      pass

def main():
   i = 0
   wdd = WatchDogDaeomn(2, 0.5)

   try:
      while 1:
         time.sleep(1)
         print 'main_' + str(i)
         i = i+1

         #wdd.ping()

   except KeyboardInterrupt:
      raise SystemExit

if __name__ == '__main__':
   main()