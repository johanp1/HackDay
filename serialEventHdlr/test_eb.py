#! /usr/bin/python
import unittest
import serialEventHandler as eh  
import comms

class EventHandlerSpy:
    def __init__(self):
        self.reset()

    def eventHandler(self, event):
        self.last_event_name = event.name
        self.last_event_data = event.data
        self.has_been_called = True

    def reset(self):
        self.last_event_name = ''
        self.last_event_data = ''
        self.has_been_called = False

class EventHandlerSpyNoArgs(EventHandlerSpy):
    def eventHandler(self):
        self.has_been_called = True

class TestEventBroker(unittest.TestCase):
    
    def setUp(self):
        self.eb = eh.EventBroker()
        self.eh1 = EventHandlerSpy()
        self.eh2 = EventHandlerSpy()
      
    def test_noHandlerAttached(self):
        self.eb.handle_event(comms.Message('foo', 'bar'))
        self.assertFalse(self.eh1.has_been_called)
        self.assertFalse(self.eh2.has_been_called)

    def test_oneHandlerAttached(self):
        self.eb.attach_handler('apa', 
                               self.eh1.eventHandler, 
                               args = (self.eb.received_event,))

        self.eb.handle_event(comms.Message('apa', '100'))
        self.assertTrue(self.eh1.has_been_called)
        self.assertFalse(self.eh2.has_been_called)
        self.assertEqual(self.eh1.last_event_name, 'apa')
        self.assertEqual(self.eh1.last_event_data, '100')

    def test_twoHandlersAttached(self):
        self.eb.attach_handler('apa', self.eh1.eventHandler, args = (self.eb.received_event,))
        self.eb.attach_handler('bepa', self.eh2.eventHandler, args = (self.eb.received_event,))

        self.eb.handle_event(comms.Message('bepa', '99'))
        
        self.assertFalse(self.eh1.has_been_called)
        self.assertTrue(self.eh2.has_been_called)
        self.assertEqual(self.eh2.last_event_name, 'bepa')
        self.assertEqual(self.eh2.last_event_data, '99')
     
    def test_handlerNoArgs(self):
        self.eh_no_args = EventHandlerSpyNoArgs()
        self.eb.attach_handler('test', self.eh_no_args.eventHandler)

        self.eb.handle_event(comms.Message('test', '99'))
        self.assertTrue(self.eh_no_args.has_been_called)  
        self.assertEqual(self.eh_no_args.last_event_name, '')
        self.assertEqual(self.eh_no_args.last_event_data, '')  
        self.eh_no_args.reset()
        
        self.eb.handle_event(comms.Message('test', ''))
        self.assertTrue(self.eh_no_args.has_been_called)
        self.assertEqual(self.eh_no_args.last_event_name, '')
        self.assertEqual(self.eh_no_args.last_event_data, '')    
        self.eh_no_args.reset()
      
    def test_wrongEvent(self):
        self.eb.attach_handler('apa', self.eh1.eventHandler, args=(self.eb.received_event,))
        self.eb.attach_handler('bepa', self.eh2.eventHandler, args=(self.eb.received_event,))

        self.eb.handle_event(comms.Message('foo', '11'))
        
        self.assertFalse(self.eh1.has_been_called)
        self.assertFalse(self.eh2.has_been_called)   

if __name__ == '__main__':
   unittest.main()