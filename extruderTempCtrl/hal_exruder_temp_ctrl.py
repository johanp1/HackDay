import getopt
import hal
import sys
import comms
import time

class HalAdapter:   
   def __init__(self, name):
      self.hal = hal.component(name)  # instanciate the HAL-component
      self.hal.newpin("ref-temp", hal.HAL_U32, hal.HAL_IN)
      self.hal.newpin("enable", hal.HAL_BIT, hal.HAL_IN)
      self.hal.newpin("curr-temp", hal.HAL_U32, hal.HAL_OUT)
      
      self.hal.ready()
 
   def setReady(self): 
      self.hal.ready()
         
   def readHAL_refTemp(self):
      """read values from LinuxCNC HAL"""
      return self.hal['ref-temp']

   def readHAL_enable(self):
      """read values from LinuxCNC HAL"""
      return self.hal['enable']

   def writeHAL_CurrTemp(self, val):
      """ write internal wrapper pin values to LinuxCNC HAL """
      self.hal['curr-temp'] = val

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
      if self.enable == False and en == 1:
         self.enable = True
         self.tempController.writeMessage(comms.Message('en' , str(en)))

   def setRefTemp(self, refT):
      if self.enable == True:
         if self.refTemp != refT:
            self.tempController.writeMessage(comms.Message('sp' , str(refT)))
            self.refTemp = refT
   

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

   h = HalAdapter(name)
   tc = TempControllerFacade(port)
   #tc.setEnable(True)
   
   try:
         while 1:
            if h.readHAL_enable() == True:
               tc.setEnable(True)

               refTemp = h.readHAL_refTemp()
               tc.setRefTemp(refTemp)               
            else:
               tc.setEnable(False)
               
            h.writeHAL_CurrTemp(tc.currTemp)

            time.sleep(1)

   except KeyboardInterrupt:
      raise SystemExit

if __name__ == '__main__':
   main()