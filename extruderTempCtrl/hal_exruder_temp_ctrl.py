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

class HalFacade:   
   def __init__(self, name):
      self.hal = hal.component(name)  # instanciate the HAL-component
      self.hal.newpin("ref-temp", hal.HAL_U32, hal.HAL_IN)
      self.hal.newpin("curr-temp", hal.HAL_U32, hal.HAL_OUT)
      self.hal.ready()
 
   def readPin(self, pin):
      return self.hal[pin]

   def updateHAL(self, currTemp):
      """ write internal wrapper pin values to LinuxCNC HAL """
      self.hal['curr-temp'] = currTemp

class MessageHandler:
   def __init__(self):
      self.currTemp = 100

   def handler(self, m):
      if (m.msg == 'mv'):
         self.currTemp = int(m.val)

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
   hdlr = MessageHandler()
   tempController = comms.instrument(port, hdlr.handler) #serial adaptor

   try:
         while 1:
            refTemp = h.readPin('ref-temp')
            tempController.writeMessage(comms.Message('sp' , str(refTemp)))
            tempController.readMessages() #update current temp
            h.updateHAL(hdlr.currTemp)
            
            time.sleep(1)

   except KeyboardInterrupt:
      raise SystemExit

if __name__ == '__main__':
   main()