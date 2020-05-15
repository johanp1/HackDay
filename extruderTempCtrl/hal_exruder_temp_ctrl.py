import getopt
import hal
import sys
import comms
import time

class Pin:
   """ Representation of a Pin and it's data"""
   def __init__(self, type, dir):
      self.val = 0    # current value of pin, e.g. 1 - on, 0 - off
      self.type = type  # type (string read from xml)
      self.dir = dir

   def __repr__(self):
      return 'val: ' + str(self.val) + '\ttype: ' + self.type + '\tdir: ' + self.dir

class HalAdapter:   
   def __init__(self, name):
      self.hal = hal.component(name)  # instanciate the HAL-component
      self.hal.newpin("ref-temp", hal.HAL_U32, hal.HAL_IN)
      self.hal.newpin("wait-temp", hal.HAL_U32, hal.HAL_IN)
      self.hal.newpin("curr-temp", hal.HAL_U32, hal.HAL_OUT)
      self.hal.newpin("temp-ok", hal.HAL_BIT, hal.HAL_OUT)
          
      self.hal.ready()
 
   def setReady(self): 
      self.hal.ready()

   def readPin(self, pin):
      return self.hal[pin]
         
   def updateHAL(self):
      """ write internal wrapper pin values to LinuxCNC HAL """
      self.hal['curr-temp'] = self.currTemp
      self.hal['temp-ok'] = self.tempOk


class TempControllerFacade:
   def __init__(self, port):
      self.tempController = comms.instrument(port, self.msgHandler) #serial adaptor
      self.currTemp = 100
      self.refTemp = 100
      self.enable = False

   def msgHandler(self, m):
      if (m.msg == 'mv'):
         self.currTemp = int(m.val)

   def setEnable(self, en):
      self.enable = en

   def setRefTemp(self, refT):
      if self.enable == True:
         self.tempController.writeMessage(comms.Message('sp' , str(refT)))

def main():
   name = 'my-extruder'
   port = '/dev/ttyUSB0'     # default serial port to use

   try:
      opts, args = getopt.getopt(sys.argv[1:], "hp:c:", ["port="])
   except getopt.GetoptError as err:
      # print help information and exit:
      print(err) # will print something like "option -a not recognized"
      sys.exit(2)

   for o, a in opts:
      if o == "-h":
         sys.exit()
      if o == "-c":
         name = a
      elif o in ("-p", "--port"):
         port = a
      else:
         print o
         assert False, "unhandled option"

   h = HalFacade(name)
   tc = TempControllerFacade(port)
   prevRefTemp = h.readPin('ref-temp')

   try:
         while 1:
            refTemp = h.readPin('ref-temp')
            if refTemp != prevRefTemp:
                
                prevRefTemp = refTemp
                
            tempController.readMessages() #update current temp
            h.updateHAL()
            
            time.sleep(1)

   except KeyboardInterrupt:
      raise SystemExit

if __name__ == '__main__':
   main()