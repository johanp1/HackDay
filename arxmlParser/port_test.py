#! /usr/bin/python

import unittest
from ArxmlParser import RPort, PPort, ValueSignal, StructSignal, StructSignalElement

class TestVisitor:
   def __init__(self):
      self.visited_pport = ''
      self.visited_rport = ''
      self.visited_signal = ''
      self.visited_element = ''

   def renderPPort(self, port):
      self.visited_pport = port.port_name
      for signal in port.signal_array:
         signal.accept(self)

   def renderRPort(self, port):
      self.visited_rport = port.port_name
      for signal in port.signal_array:
         signal.accept(self)

   def renderValueSignal(self, signal):
      self.visited_signal = signal.name

   def renderStructSignal(self, signal):
      self.visited_signal = signal.name
      for element in signal.element_array:
         element.accept(self)

   def renderStructElement(self, element):
      self.visited_element = element.name

class TestPort(unittest.TestCase):
   def setUp(self):
      self.visitor = TestVisitor()

   def test_init_pport(self):
      p = RPort('test_rport', 'rport_if')
            
      self.assertTrue(p.port_name == 'test_rport')
      self.assertTrue(p.port_if == 'rport_if')
      self.assertTrue(p.direction == 'required')
      self.assertTrue(len(p.signal_array) == 0)

   def test_init_rport(self):
      p = PPort('test_pport', 'pport_if')
            
      self.assertTrue(p.port_name == 'test_pport')
      self.assertTrue(p.port_if == 'pport_if')
      self.assertTrue(p.direction == 'provided')
      self.assertTrue(len(p.signal_array) == 0)

   def test_visit_pport(self):
      p = PPort('test_pport', 'pport_if')

      p.accept(self.visitor)
      self.assertTrue(self.visitor.visited_pport == 'test_pport')
      self.assertTrue(self.visitor.visited_rport == '')
      
   def test_visit_rport(self):
      p = RPort('test_rport', 'rport_if')

      p.accept(self.visitor)
      self.assertTrue(self.visitor.visited_pport == '')
      self.assertTrue(self.visitor.visited_rport == 'test_rport')

   def test_visit_value_signal(self):
      p = RPort('rport', 'rport_if')
      p.signal_array.append(ValueSignal('signal', 'signal_type'))
      p.accept(self.visitor)
      self.assertTrue(len(p.signal_array) == 1)
      self.assertTrue(self.visitor.visited_rport == 'rport')
      self.assertTrue(self.visitor.visited_signal == 'signal')

   def test_visit_struct_signal(self):
      p = RPort('rport', 'rport_if')
      p.signal_array.append(StructSignal('struct_signal', 'struct_type'))
      p.signal_array[0].element_array.append(StructSignalElement('element1', 'element1_type'))

      p.accept(self.visitor)
      self.assertTrue(len(p.signal_array) == 1)
      self.assertTrue(len(p.signal_array[0].element_array) == 1)
      self.assertTrue(self.visitor.visited_rport == 'rport')
      self.assertTrue(self.visitor.visited_signal == 'struct_signal')
      self.assertTrue(self.visitor.visited_element == 'element1')

if __name__ == '__main__':
   unittest.main()