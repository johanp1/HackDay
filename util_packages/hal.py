#! /usr/bin/python
HAL_BIT   = 'HAL_BIT'
HAL_S32   = 'HAL_S32'
HAL_U32   = 'HAL_U32'
HAL_FLOAT = 'HAL_FLOAT'
HAL_OUT   = 'HAL_OUT'
HAL_IO    = 'HAL_IO'
HAL_IN    = 'HAL_IN'
HAL_RO    = 'HAL_RO' 
HAL_RW    = 'HAL_RW'

class HalPin:
   """stub sub class to component class"""   
   def __init__(self, name, type, dir):
      self.name = name
      self.type = type
      self.dir = dir
      self.val = 0

   def __repr__(self):
      return 'HAL pin name: ' + self.name + ' val: ' + str(self.val) + ' type: ' + self.type

class HalPar:
   """stub sub class to component class"""   
   def __init__(self, name, type, dir):
      self.name = name
      self.type = type
      self.dir = dir
      self.val = 0

   def __repr__(self):
      return 'HAL parameter name: ' + self.name + ' val: ' + str(self.val) + ' type: ' + self.type

class component:
   """stub class linuxCNC hal-api"""
   
   def __init__(self, name):
      self.pinDict = {}
      self.parDict = {}
      self.readyFlag = 0
      self.name = name
      
   def newpin(self, _pinName, _pinType, _pinDir):
      pinName = _pinName.strip('"')
      self.pinDict[pinName] = HalPin(pinName, _pinType, _pinDir)

   def newpar(self, _parName, _parType, _parDir):
      parName = _parName.strip('"')
      self.parDict[parName] = HalPar(parName, _parType, _parDir)

   def ready(self):
      self.readyFlag = 1

   def __getitem__(self, name):
      if name in self.pinDict:
         return self.pinDict[name].val
      if name in self.parDict:
         return self.parDict[name].val

   def __setitem__(self, name, val):
      if name in self.pinDict and self.pinDict[name].val != val:
         self.pinDict[name].val = val
         print name + ': ' + str(val)
      if name in self.parDict:
         self.parDict[name].val = val
