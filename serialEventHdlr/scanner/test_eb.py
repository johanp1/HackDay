#! /usr/bin/python
import unittest
import scanner  

class EventHandlerSpy:
    def __init__(self):
        self.reset()

    def event_handler(self, message_payload):
        self.last_event_data = message_payload
        self.has_been_called = True

    def reset(self):
        self.last_event_data = ''
        self.has_been_called = False

class EventHandlerSpy2arg:
    def __init__(self):
        self.reset()

    def event_handler(self, message_payload1, message_payload2):
        self.last_event_data = [message_payload2, message_payload1]
        self.has_been_called = True

    def reset(self):
        self.last_event_data = ''
        self.has_been_called = False

class EventHandlerSpyNoArgs(EventHandlerSpy):
    def event_handler(self):
        self.has_been_called = True

class TestEventBroker(unittest.TestCase):
    
    def setUp(self):
        self.eb = scanner.MessageBroker()
        self.eh1 = EventHandlerSpy()
        self.eh2 = EventHandlerSpy2arg()
      
    def test_no_handler_attached(self):
        self.eb.message_handler('foo_bar')
        self.assertFalse(self.eh1.has_been_called)
        self.assertFalse(self.eh2.has_been_called)

    def test_simple_handler_attached(self):
        self.eb.attach_handler('apa', 
                               self.eh1.event_handler)

        self.eb.message_handler('apa_100')
        self.assertTrue(self.eh1.has_been_called)
        self.assertFalse(self.eh2.has_been_called)
        self.assertEqual(self.eh1.last_event_data, '100')

    def test_two_arg_handler_attached(self):
        self.eb.attach_handler('bepa', 
                               self.eh2.event_handler)

        self.eb.message_handler('bepa_100_300')
        self.assertTrue(self.eh2.has_been_called)
        self.assertFalse(self.eh1.has_been_called)
        self.assertEqual(self.eh2.last_event_data, ['300', '100'])

    def test_wrong_num_of_args(self):
        self.eb.attach_handler('apa', 
                               self.eh1.event_handler)

        self.eb.message_handler('apa_100_2')
        self.assertFalse(self.eh1.has_been_called)
        self.assertFalse(self.eh2.has_been_called)

        self.eb.message_handler('apa')
        self.assertFalse(self.eh1.has_been_called)
        self.assertFalse(self.eh2.has_been_called)

    def test_wrong_event_name(self):
        self.eb.attach_handler('apa', 
                               self.eh1.event_handler)

        self.eb.message_handler('bepa_100')
        self.assertFalse(self.eh1.has_been_called)
        self.assertFalse(self.eh2.has_been_called)

    def test_handler_no_args(self):
        self.eh_no_args = EventHandlerSpyNoArgs()
        self.eb.attach_handler('test', self.eh_no_args.event_handler)
        
        self.eb.message_handler('test')
        self.assertTrue(self.eh_no_args.has_been_called)
        self.eh_no_args.reset()

if __name__ == '__main__':
   unittest.main()