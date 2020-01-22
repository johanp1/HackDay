#! /usr/bin/python

import sys
import getopt
import xml.etree.ElementTree as ET
import hal
import time

class Pin:
   """ Representation of a Pin and it's data"""
   def __init__(self, type, dir):
      self.val = 0    # current value of pin, e.g. 1 - on, 0 - off
      self.type = type  # type (string read from xml)
      self.dir = dir

   def __repr__(self):
      return 'val: ' + str(self.val) + '\ttype: ' + self.type + '\tdir: ' + self.dir

class ComponentWrapper:   
   def __init__(self, name):
      self.hal = hal.component(name)  # instanciate the HAL-component
      self.pinDict = {}

   def __repr__(self):
      tmp_str = ''
      for k in self.pinDict:
         tmp_str += 'name: ' + k + '\t' + str(self.pinDict[k].val) + '\n'
      return tmp_str

   def addPin(self, name, type, dir):
      self.pinDict[name] = Pin(type, dir)
      self._addHALPin(name, type, dir)
            
   def setReady(self): 
      self.hal.ready()

   def setPin(self, pin_name, val):
      self.pinDict[pin_name].val = val
      self.hal[pin_name] = self.pinDict[pin_name].val

   def readPin(self, pin_name):
      self.pinDict[pin_name].val = self.hal[pin_name]
      return self.pinDict[pin_name].val

   def updateHAL(self):
      for key in self.pinDict:
         if self.pinDict[key].dir == 'out':
            self.hal[key] = self.pinDict[key].val

   def _addHALPin(self, pin_name, type, pin_dir):
      self.hal.newpin(pin_name, self._getHALType(type), self._getHalPinDir(pin_dir))  # create the user space HAL-pin

   def _getHALType(self, str):
      """ helper function to convert type read from xml to HAL-type """
      retVal = ''
   
      if str == 'bit':
         retVal = hal.HAL_BIT
	
      if str == 'float':
         retVal = hal.HAL_FLOAT

      if str == 's32':
         retVal = hal.HAL_S32

      if str == 'u32':
         retVal = hal.HAL_U32
      return retVal 

   def _getHalPinDir(self, str):
      """ helper function to convert pin direction to HAL-pin direction type """
      retVal = ''
   
      if str == 'in':
         retVal = hal.HAL_IN
	
      if str == 'out':
         retVal = hal.HAL_OUT
      
      return retVal

class parameterContainer:
   def __init__(self, xml_file):
      self.paramDict = {}
      self._xmlFile = xml_file

      self.tree = ET.parse(self._xmlFile)
      self._parse()

   def _parse(self):
      root = self.tree.getroot()
      for param in root.iter('parameter'):
         #print param.attrib['name'], param.attrib['value'] 
         self.paramDict[param.attrib['name']] = float(param.attrib['value'])

   def getParam(self, name):
      if name in self.paramDict:
         return self.paramDict[name]
      else:
         return None 

   def getParams(self):
      return self.paramDict

   def writeToFile(self):
      for parName in self.paramDict:
         self._writeToTree(parName, self.paramDict[parName])

      self.tree.write(self._xmlFile)

   def writeParam(self, parName, value):
      if parName in self.paramDict:
         self.paramDict[parName] = value

   def _writeToTree(self, parName, value):   
      """update parameter in xml-tree"""
      root = self.tree.getroot()
      
      for param in root.iter('parameter'):
           if param.attrib['name'] == parName:
               param.attrib['value'] = str(value)
               break


def usage():
    print 'usage luber.py --input=<in-file> --debug=[01]'

def main():
   paramDict = {}
   debug = 0
   xmlFile = 'luber.xml'
   name = 'my-luber'       # default name of component in HAL

   try:
        opts, args = getopt.getopt(sys.argv[1:], "h", ["input=", "debug="])
   except getopt.GetoptError as err:
      # print help information and exit:
      print(err) # will print something like "option -a not recognized"
      sys.exit(2)

      for o, a in opts:
         if o == "-h":
            usage()
            sys.exit()
         elif o == "--input":
            xmlFile = a
         elif o == "--debug":
            debug = a
         else:
            print o
            assert False, "unhandled option"

   p = parameterContainer(xmlFile)

   c = ComponentWrapper(name) #HAL adaptor
   c.addPin('x-vel-cmd', 'u32', 'in')
   c.addPin('y-vel-cmd', 'u32', 'in')
   c.addPin('z-vel-cmd', 'u32', 'in')
   c.addPin('lube', 'bit', 'out')
   print c

   # ready signal to HAL, component and it's pins are ready created
   c.setReady()
   
   totalDistance = p.getParam('totalDistance')
   distanceThreshold = p.getParam('distanceThreshold')
   
   prevTime = time.time()

   try:
      while 1:
         currentTime =  time.time()
         timeDelta = currentTime - prevTime
         #print timeDelta
         totalDistance += abs(c.readPin('x-vel-cmd')) * timeDelta
         totalDistance += abs(c.readPin('y-vel-cmd')) * timeDelta
         totalDistance += abs(c.readPin('z-vel-cmd')) * timeDelta

         if totalDistance >= distanceThreshold:
            print 'runLubeCycle()'
            totalDistance = 0

         p.writeParam('totalDistance', int(totalDistance))

         c.updateHAL()

         prevTime = currentTime

         time.sleep(0.1)

   except KeyboardInterrupt:
      
      p.writeToFile()
      raise SystemExit

class LubeControl:
   def __init__(self, lube_cycle_time, lube_on_time, nbr_of_pulses_per_cycle, accumulated_distance, distance_threshold, init_time):
      self.lubeCycleTime = lube_cycle_time
      self.lubeOnTime = lube_on_time
      self.pulsesPerCycle = nbr_of_pulses_per_cycle
      self.totalDistance = accumulated_distance
      self.distanceThreshold = distance_threshold
      self.state = 'OFF'
      self.prevTime = init_time

   def calcDistFromVel(self, dxdt, dydt, dzdt, timeStamp):
      timeDelta = timeStamp - self.prevTime

      self.totalDistance += abs(dxdt) * timeDelta
      self.totalDistance += abs(dydt) * timeDelta
      self.totalDistance += abs(dzdt) * timeDelta

      self.prevTime = timeStamp

   def runStateMachine(self):
      if self.totalDistance >= self.distanceThreshold:
         self.state = 'ON'
         self.totalDistance = 0

      if self.state == 'ON':
         pass

if __name__ == '__main__':
   main()