#! /usr/bin/pythone

import sys
import comms
import hal
import getopt
import time      

class FakeEncoder:
   def __init__(self, dT, scale):
      self._position = 0  # scaled value from count
      self._velocity = 0  # units per sec, i.e. rps
      self._dT = dT       # delta time between samples [s]
      self._scale = scale # nbr of pulses / rev

   def clear(self):
      self._position = 0
      print('FakeEncoder::clearing position data')

   def handleEvent(self, event):
      if (event.name == 'pos'):
         self._velocity = float(event.data)/(self._scale*self._dT) #pos per dT to rps
         self._position += float(event.data)/self._scale

   def getVelocity(self):
      return self._velocity

   def getPosition(self):
      return self._position


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
               print(o, a)
               assert False, "unhandled option"
         
               
   def getName(self):
      return self.name

   def getPort(self):
      return self.port
   
   def _usage(self):
      """ print command line options """
      print("usage serial_mpg.py -h -c <name> -p/--port= <serial port>\n"\
         "-c <name>                # name of component in HAL. 'mpg' default\n"\
         "-p/--port= <serial port> # default serial port to use. '/dev/ttyS2' default\n"\
         "-h                       # print this test")


def main():
   optParser = OptParser(sys.argv[1:])
   componentName = optParser.getName()
   portName = optParser.getPort()

   print(optParser)

   fakeEncoder = FakeEncoder(0.05, 500)
   speedCounter = comms.instrument(portName, fakeEncoder.handleEvent, False) #serial adaptor, watchdog disabled
   halAdapter = HalAdapter(componentName, fakeEncoder.clear)

   try:
      while 1:
         speedCounter.enableWatchdog(halAdapter.isWatchdogEnabled())
         speedCounter.readMessages()
            
         halAdapter.update(fakeEncoder.getVelocity(), fakeEncoder.getPosition())
      
         time.sleep(0.05)

   except KeyboardInterrupt:
      raise SystemExit

if __name__ == '__main__':
   main()
