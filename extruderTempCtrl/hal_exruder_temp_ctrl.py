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
      self.hal.newpin("ref-temp-out", hal.HAL_U32, hal.HAL_OUT)
      
      self.hal.ready()
 
   def setReady(self): 
      self.hal.ready()
         
   def readHAL_refTemp(self):
      """read values from LinuxCNC HAL"""
      return self.hal['ref-temp']

   def readHAL_enable(self):
      """read values from LinuxCNC HAL"""
      return self.hal['enable']

   def writeHAL_currTemp(self, val):
      """ write internal wrapper pin values to LinuxCNC HAL """
      self.hal['curr-temp'] = val
      
   def writeHAL_refTemp(self, val):
      """ write internal wrapper pin values to LinuxCNC HAL """
      self.hal['ref-temp-out'] = val

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

      if en == True:   
         self.tempController.writeMessage(comms.Message('en' , '1'))
      else:
         self.tempController.writeMessage(comms.Message('en' , '0'))

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
            tc.tempController.readMessages()

            if h.readHAL_enable() == 1:
               if tc.enable == False:
                  tc.setEnable(True)               
            else:
               tc.setEnable(False)

            if tc.enable == True:
               refTemp = h.readHAL_refTemp()
               tc.setRefTemp(refTemp)   

            h.writeHAL_currTemp(tc.currTemp)
            h.writeHAL_refTemp(tc.refTemp);

            time.sleep(1)

   except KeyboardInterrupt:
      raise SystemExit

if __name__ == '__main__':
   main()