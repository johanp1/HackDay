import threading
import Queue as queue
import time

class inputDeamon(threading.Thread):
   def __init__(self):
      self.inputQueue = queue.Queue()

      threading.Thread.__init__(self)
      self.daemon=True
      self.start()
      self.input_str = ''

   def get_input(self):
      if (self.inputQueue.qsize() > 0):
         return self.inputQueue.get()


   def run(self):
      while (True):
         try:
            self.input_str = raw_input()
         except EOFError: 
            raise SystemExit

         self.inputQueue.put(self.input_str)
         time.sleep(0.01) 


def main():
   id = inputDeamon()
   while 1: 
      print "input_str = {}".format(id.get_input())
      time.sleep(0.1)

if (__name__ == '__main__'): 
    main()