#! /usr/bin/python
""" currently not used..."""

import comms 

class BrokeeContainer:
   def __init__(self, handler, args):
      self.handler = handler
      self.args = args

class EventBroker:
   def __init__(self):
      self.brokee_dict = {}
      self.received_event = comms.Message('')

   def attach_handler(self, event_name, handler, args = ()):
      self.brokee_dict[event_name] = BrokeeContainer(handler, args)

   def handle_event(self, event):
      self.received_event.copy(event)

      if event.name in self.brokee_dict:            
         self.brokee_dict[event.name].handler(*self.brokee_dict[event.name].args)