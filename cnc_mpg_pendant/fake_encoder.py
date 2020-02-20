#! /usr/bin/pythone

import sys
import comms
import hal
import getopt
import time

class FakeEncoder:
   def __init__(self):
      self.position = 0 #scaled value from count
      self.velocity = 0 #units per sec, i.e. rps
      self.count = 0    #number of pulses received
      self.scale = 500
        
   def clear(self):
      self.position = 0
      self.count = 0 
        
   def handleEvent(self, event):
      if (event.ev == 'rpm'):
         self.count += int(event.val)
         self.velocity = int(event.val)/60 #rpm to rps
         self.position = self.count/self.scale 
       
class HalFacade:
   def __init__(self, name, clear_cb):
      self.h = hal.component(name) 
      self.clearCallback = clear_cb

      self.h.newpin("velocity", hal.HAL_FLOAT, hal.HAL_OUT)
      self.h.newpin("position", hal.HAL_FLOAT, hal.HAL_OUT)
      self.h.newpin("index-enable", hal.HAL_BIT, hal.HAL_IO)
      self.h.ready()

   def update(self, vel, pos):
      self.h['velocity'] = vel
      self.h['position'] = pos

      if self.h['index-enable'] == 1:
         self.clearCallback()
         self.h['position'] = 0
         self.h['index-enable'] = 0

class OptParser:
   def __init__(self, argv):
      self.name = 'my-fake-encoder'  # default name of component in HAL
      self.port = '/dev/ttyUSB1'     # default serial port to use
      
      self._getOptions(argv)
      
   def __repr__(self):
      return 'name: ' + self.name + '\tport: ' + self.port
      
   def _getOptions(self, argv):
      if argv != []:
         try:
            opts = getopt.getopt(argv, "hp:c:", ["port="])
         except getopt.GetoptError as err:
            # print help information and exit:
            print(err) # will print something like "option -a not recognized"
            sys.exit(2)

         ### parse input command line
         for o, a in opts:
            if o == "-h":
               self._usage()
               sys.exit()
            if o == "-c":
               self.name = a
            elif o in ("-p", "--port"):
               self.port = a
            else:
               print o
               assert False, "unhandled option"
         
               
   def getName(self):
      return self.name

   def getPort(self):
      return self.port
   
   def _usage(self):
      """ print command line options """
      print "usage serial_mpg.py -h -c <name> -p/--port= <serial port>\n"\
         "-c <name>                # name of component in HAL. 'mpg' default\n"\
         "-p/--port= <serial port> # default serial port to use. '/dev/ttyS2' default\n"\
         "-h                       # print this test"

def main():
   optParser = OptParser(sys.argv[1:])
   componentName = optParser.getName()
   portName = optParser.getPort()
   print optParser

   fake = FakeEncoder()
   speedCounter = comms.instrument(portName, fake.handleEvent) #serial adaptor
   h = HalFacade(componentName, fake.clear)

   #h.newpin("velocity", hal.HAL_FLOAT, hal.HAL_OUT)
   #h.newpin("position", hal.HAL_FLOAT, hal.HAL_OUT)
   #h.newpin("index-enable", hal.HAL_BIT, hal.HAL_IO)
   #h.ready()
    
   try:
      while 1:
         speedCounter.readEvents() #blocks until '\n' received or timeout
            
         h.update(fake.velocity, fake.position)
            
         time.sleep(0.1)

   except KeyboardInterrupt:
      raise SystemExit

if __name__ == '__main__':
   main()
