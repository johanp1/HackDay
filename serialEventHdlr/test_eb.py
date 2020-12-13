#! /usr/bin/python
import unittest
import serialEventHandler as eh  

class EventHandlerSpy:
    def __init__(self):
        self.has_been_called = False

    def eventHandler(self, event_name, data):
        self.last_event = event_name
        self.last_data = data
        self.has_been_called = True

    def reset(self):
        pass

class TestEventBroker(unittest.TestCase):
    
    def setUp(self):
        self.eb = eh.EventBroker()
        self.eh1 = EventHandlerSpy()
        self.eh2 = EventHandlerSpy()
      
    def test_noHandlerAttached(self):
        self.eb.handle_event('foo', 'bar')
        self.assertFalse(self.eh1.has_been_called)
        self.assertFalse(self.eh2.has_been_called)

    def test_oneHandlerAttached(self):
        self.eb.attach_handler('apa', self.eh1.eventHandler)

        self.eb.handle_event('apa', '100')
        self.assertTrue(self.eh1.has_been_called)
        self.assertFalse(self.eh2.has_been_called)

    def test_TwoHandlersAttached(self):
        self.eb.attach_handler('apa', self.eh1.eventHandler)
        self.eb.attach_handler('bepa', self.eh2.eventHandler)

        self.eb.handle_event('bepa', '99')
        
        self.assertFalse(self.eh1.has_been_called)
        self.assertTrue(self.eh2.has_been_called)
        
    def test_wrongEvent(self):
        self.eb.attach_handler('apa', self.eh1.eventHandler)
        self.eb.attach_handler('bepa', self.eh2.eventHandler)

        self.eb.handle_event('foo', '11')
        
        self.assertFalse(self.eh1.has_been_called)
        self.assertFalse(self.eh2.has_been_called)   

if __name__ == '__main__':
   unittest.main()