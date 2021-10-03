#! /usr/bin/python

import sys
import getopt
import xml.etree.ElementTree as ET
import hal
import time
from collections import namedtuple

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
      self.h = hal.component(name) 
      self.h.newpin("velocity", hal.HAL_FLOAT, hal.HAL_OUT)
      self.h.newpin('x-vel', hal.HAL_FLOAT, hal.HAL_IN)
      self.h.newpin('y-vel', hal.HAL_FLOAT, hal.HAL_IN)
      self.h.newpin('z-vel', hal.HAL_FLOAT, hal.HAL_IN)
      self.h.newpin('lube-level-ok',hal.HAL_BIT, hal.HAL_IN)
      self.h.newpin('reset', hal.HAL_BIT, hal.HAL_IN)
      self.h.newpin('lube-ext-req', hal.HAL_BIT, hal.HAL_IN)
      self.h.newpin('lube-cmd', hal.HAL_BIT, hal.HAL_OUT)
      self.h.newpin('lube-level-alarm', hal.HAL_BIT, hal.HAL_OUT)
      self.h.newpin('accumulated-distance', hal.HAL_FLOAT, hal.HAL_OUT)
      self.h.ready()

   def __repr__(self):
      tmp_str = ''
      return tmp_str

   def is_lube_level_ok(self):
      return self.h['lube-level-ok']

   def is_reset(self):
      return self.h['reset']

   def is_lube_ext_req(self):
      return self.h['lube-ext-req']

   def get_velocities(self):
      velocities = namedtuple("velocities", ["x", "y", "z"])
      return velocities(
         self.h['x-vel'],
         self.h['y-vel'],
         self.h['z-vel'])

   def set_lube_on(self,  request):
      if request >= 1:
         self.h['lube-cmd'] = 1
      else:
         self.h['lube-cmd'] = 0

   def set_lube_level_alarm(self, level_ok):
      if level_ok >= 1:
         self.h['lube-level-alarm'] = 1
      else:
         self.h['lube-level-alarm'] = 0

   def set_accumulated_distance(self, d):
      self.h['accumulated-distance'] = d

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
               param.attrib['value'] = str(round(value, 2))
               break


class LubeControl:
   def __init__(self, lube_on_time, accumulated_distance, distance_threshold, number_of_lubings):
      self.lubeOnTime = lube_on_time                   # [sec]
      self.total_distance = accumulated_distance       # [mm]
      self.distance_threshold = distance_threshold     # [mm]
      self.numberOfLubings = number_of_lubings

      self.state = 'OFF'
      self.lubeLevelOkOut = True
      self._lubeLevelOkIn = True
      self.prev_time = time.time()

   def calc_dist_from_vel(self, v_x, v_y, v_z):
      current_time = time.time()
      time_delta = current_time - self.prev_time

      self.total_distance += abs(v_x) * time_delta
      self.total_distance += abs(v_y) * time_delta
      self.total_distance += abs(v_z) * time_delta

      self.prev_time = current_time


   def runStateMachine(self, ext_req):
      currentTime = time.time()
      if self.total_distance >= self.distance_threshold or ext_req == True:
         self.state = 'ON'
         self.timeout = self.lubeOnTime + currentTime
         self.total_distance = 0
         self.numberOfLubings += 1

      if self.state == 'ON':
         if currentTime > self.timeout:
            #check lube pressure sensor
            self.lubeLevelOkOut = self._lubeLevelOkIn

            self.state = 'OFF'
               

   def setLubeLevelOK(self, levelOk):
      self._lubeLevelOkIn = levelOk

   def reset(self):
      self.total_distance = 0
      self.state = 'OFF'
      self.lubeLevelOkOut = True

def _usage():
   """ print command line options """
   print "usage luber.py -h -c<name> <path/>in_file.xml\n"\
      "in_file         # input xml-file describing what knobs and/or button are on the pendant\n"\
      "-c <name>       # name of component in HAL. 'my-luber' default\n"\
      "-h              # Help test"

def main():
   xmlFile = 'luber.xml'
   #xmlFile = ''
   name = 'my-luber'       # default name of component in HAL

   try:
        opts, args = getopt.getopt(sys.argv[1:], "hc:", ["input="])
   except getopt.GetoptError as err:
      # print help information and exit:
      print(err) # will print something like "option -a not recognized"
      sys.exit(2)

   for o, a in opts:
      if o == "-h":
         _usage()
         sys.exit()
      elif o == "-c":
         name = a
      elif o == "--input":
         xmlFile = a
      else:
         print o
         assert False, "unhandled option"

   if xmlFile == '':
      if len(sys.argv) < 2:
         _usage()
         sys.exit(2)
      else:
         xmlFile = sys.argv[-1]
            
   p = parameterContainer(xmlFile)

   h = HalAdapter(name) 
   
   totalDistance = p.getParam('totalDistance')
   distanceThreshold = p.getParam('distanceThreshold')
   lubeOnTime = p.getParam('lubePulseTime')
   nbrOfLubings = p.getParam('numberOfLubings')

   lubeCtrl = LubeControl(lubeOnTime, totalDistance, distanceThreshold, nbrOfLubings)

   try:
      while 1:
         if h.is_reset():
            lubeCtrl.reset()

         lubeCtrl.setLubeLevelOK(h.is_lube_level_ok())
         v = h.get_velocities()
         lubing_external_request = h.is_lube_ext_req()
         lubeCtrl.calc_dist_from_vel(v.x, v.y, v.z)

         lubeCtrl.runStateMachine(lubing_external_request)

         h.set_lube_on(lubeCtrl.state == 'ON')
         h.set_lube_level_alarm(lubeCtrl.lubeLevelOkOut)
         h.set_accumulated_distance(lubeCtrl.total_distance)

         time.sleep(0.1)

   except KeyboardInterrupt:
      p.writeParam('totalDistance', lubeCtrl.total_distance)
      p.writeParam('numberOfLubings', lubeCtrl.numberOfLubings)
      p.writeToFile()
      raise SystemExit

if __name__ == '__main__':
   main()
