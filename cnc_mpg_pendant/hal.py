#! /usr/bin/python
HAL_BIT = 'HAL_BIT'
HAL_S32 = 'HAL_S32'
HAL_U32 = 'HAL_U32'
HAL_OUT = 'HAL_OUT'

class hal_pin:
   """stub sub class to component class"""   
   def __init__(self, name, type):
      self.name = name
      self.type = type
      self.val = 0
      
   def __repr__(self):
      return 'HAL pin name: ' + self.name + ' val: ' + str(self.val)
      
class component:
   """stub class linuxCNC hal-api"""
   
   def __init__(self, name):
      self.pin_list = []
      self.ready_flag = 0;
      self.name = name
      
   def newpin(self, pin_name, pin_type, dir):
      self.pin_list.append(hal_pin(pin_name.strip('"'), pin_type))

   def ready(self):
      self.ready_flag = 1

   def __getitem__(self, name):
      for pin in self.pin_list:
         if pin.name == name:
            return pin

   def __setitem__(self, name, val):
      for pin in self.pin_list:
         if pin.name == name:
            pin.val = val
