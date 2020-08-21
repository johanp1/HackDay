#! /usr/bin/python
import unittest
import serialEventHandler as eh
import comms  

class EventHandlerSpy:
    def __init__(self):
        self.hasBeenCalled = False

    def eventHandler(self, event):
        self.lastEvent = event
        self.hasBeenCalled = True

    def reset(self):
        pass

class TestEventBroker(unittest.TestCase):
    
    def setUp(self):
        self.eb = eh.EventBroker()
        self.eh1 = EventHandlerSpy()
        self.eh2 = EventHandlerSpy()
      
    def test_noHandlerAttached(self):
        self.eb.handleEvent(comms.Message('foo', 'bar'))
        self.assertFalse(self.eh1.hasBeenCalled)
        self.assertFalse(self.eh2.hasBeenCalled)

    def test_oneHandlerAttached(self):
        self.eb.attachHandler('apa', self.eh1.eventHandler)

        self.eb.handleEvent(comms.Message('apa', '100'))
        self.assertTrue(self.eh1.hasBeenCalled)
        self.assertFalse(self.eh2.hasBeenCalled)

    def test_TwoHandlersAttached(self):
        self.eb.attachHandler('apa', self.eh1.eventHandler)
        self.eb.attachHandler('bepa', self.eh2.eventHandler)

        self.eb.handleEvent(comms.Message('bepa', '99'))
        
        self.assertFalse(self.eh1.hasBeenCalled)
        self.assertTrue(self.eh2.hasBeenCalled)
        
    def test_wrongEvent(self):
        self.eb.attachHandler('apa', self.eh1.eventHandler)
        self.eb.attachHandler('bepa', self.eh2.eventHandler)

        self.eb.handleEvent(comms.Message('foo', '11'))
        
        self.assertFalse(self.eh1.hasBeenCalled)
        self.assertFalse(self.eh2.hasBeenCalled)   

if __name__ == '__main__':
   unittest.main()