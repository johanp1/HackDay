#! /usr/bin/pythone

import sys
import comms
import hal
import getopt
import time
import watchdog

class FakeEncoderFacade:
   """ Facade for the entire encoder subsystem (serial com, watchdog, faked encoder)
    The <enabled> argument will control if the watchdog thread is running or not"""
   def __init__(self, portName, dT, scale, wd_enabled):

      self.fakeEncoder = FakeEncoder(dT, scale)
      self.speedCounter = comms.instrument(portName, self.handleEvent) #serial adaptor
      self.wdd = watchdog.WatchDogDaemon(2, 0.5, wd_enabled)
      self.wdd.reset = self.reset
      
   def reset(self):
      self.speedCounter.close()
      print 'closing com-port'

   def handleEvent(self, event_name, data):
      self.fakeEncoder.handleEvent(event_name, data)
      self.wdd.ping() #ping watchdog

   def update(self):
      if self.speedCounter.portOpened:
         self.speedCounter.readMessages() #blocks until '\n' received or timeout
      else:
         self.speedCounter.open()
         print 'opening com-port'

   def clear(self):
      self.fakeEncoder.clear()

   def getVelocity(self):
      return self.fakeEncoder.velocity

   def getPosition(self):
      return self.fakeEncoder.position

   def enableWatchdog(self, enabled):
      self.wdd.setEnabled(enabled)
      

class FakeEncoder:
   def __init__(self, dT, scale):
      self.position = 0  # scaled value from count
      self.velocity = 0  # units per sec, i.e. rps
      self.dT = dT       # delta time between samples [s]
      self.scale = scale # nbr of pulses / rev

   def clear(self):
      self.position = 0
      print 'FakeEncoder::clearing position data'

   def handleEvent(self, event_name, data):
      if (event_name == 'pos'):
         self.velocity = float(data)/(self.scale*self.dT) #pos per dT to rps
         self.position += float(data)/self.scale

class HalAdapter:
   def __init__(self, name, clear_cb):
      self.h = hal.component(name) 
      self.clearCallback = clear_cb

      self.h.newpin("velocity", hal.HAL_FLOAT, hal.HAL_OUT)
      self.h.newpin("position", hal.HAL_FLOAT, hal.HAL_OUT)
      self.h.newpin("index-enable", hal.HAL_BIT, hal.HAL_IO)
      self.h.newpin("watchdog-enable", hal.HAL_BIT, hal.HAL_IN)
      self.h.ready()

   def update(self, vel, pos):
      self.h['velocity'] = vel
      self.h['position'] = pos

      if self.h['index-enable'] == 1:
         self.clearCallback()
         self.h['position'] = 0
         self.h['index-enable'] = 0

   def isWatchdogEnabled(self):
      return self.h['watchdog-enable']

class OptParser:
   def __init__(self, argv):
      self.name = 'my-encoder'  # default name of component in HAL
      self.port = '/dev/ttyUSB1'     # default serial port to use
      
      self._getOptions(argv)
      
   def __repr__(self):
      return 'name: ' + self.name + '\tport: ' + self.port
      
   def _getOptions(self, argv):
      if argv != []:
         try:
            opts, args = getopt.getopt(argv, "hp:c:", ["port="])
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
               print o, a
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

   fake = FakeEncoderFacade(portName, 0.05, 500, False)
   h = HalAdapter(componentName, fake.clear)

   try:
      while 1:
         fake.enableWatchdog(h.isWatchdogEnabled())
         fake.update()
            
         h.update(fake.getVelocity(), fake.getPosition())
      
         time.sleep(0.05)

   except KeyboardInterrupt:
      raise SystemExit

if __name__ == '__main__':
   main()
