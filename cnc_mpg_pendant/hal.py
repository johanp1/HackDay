#! /usr/bin/python
HAL_BIT   = 'HAL_BIT'
HAL_S32   = 'HAL_S32'
HAL_U32   = 'HAL_U32'
HAL_FLOAT = 'HAL_FLOAT'
HAL_OUT   = 'HAL_OUT'
HAL_IO   = 'HAL_IO'

class hal_pin:
   """stub sub class to component class"""   
   def __init__(self, name, type, dir):
      self.name = name
      self.type = type
      self.dir = dir
      self.val = 0

   def __repr__(self):
      return 'HAL pin name: ' + self.name + ' val: ' + str(self.val) + ' type: ' + self.type
      
class component:
   """stub class linuxCNC hal-api"""
   
   def __init__(self, name):
      self.pinDict = {}
      self.ready_flag = 0
      self.name = name
      
   def newpin(self, pin_name, pin_type, dir):
      pinName = pin_name.strip('"')
      self.pinDict[pinName] = hal_pin(pinName, pin_type, dir)

   def ready(self):
      self.ready_flag = 1

   def __getitem__(self, name):
      if name in self.pinDict:
         return self.pinDict[name].val

   def __setitem__(self, name, val):
      if name in self.pinDict:
         self.pinDict[name].val = val
