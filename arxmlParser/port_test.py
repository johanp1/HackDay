#! /usr/bin/python

import unittest
from ArxmlParser import RPort, PPort, ValueSignal, StructSignal, StructSignalElement, ValueType, ArrayType, StructType

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

   def test_init_rport(self):
      p = RPort('test_rport', 'rport_if')
            
      self.assertTrue(p.port_name == 'test_rport')
      self.assertTrue(p.port_if == 'rport_if')
      self.assertTrue(len(p.signal_array) == 0)

   def test_init_pport(self):
      p = PPort('test_pport', 'pport_if')
            
      self.assertTrue(p.port_name == 'test_pport')
      self.assertTrue(p.port_if == 'pport_if')
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
      value_type = ValueType('signal_type')
      p.signal_array.append(value_type.create_signal('signal'))
      p.accept(self.visitor)
      self.assertTrue(len(p.signal_array) == 1)
      self.assertTrue(self.visitor.visited_rport == 'rport')
      self.assertTrue(self.visitor.visited_signal == 'signal')

   def test_visit_struct_signal(self):
      p = RPort('rport', 'rport_if')
      struct_type = StructType('struct_type')
      struct_type.add_element('element1', 'element1_type')
      struct_type.add_element('element2', 'element2_type')
      p.signal_array.append(struct_type.create_signal('struct_signal'))
      
      p.accept(self.visitor)
      self.assertTrue(len(p.signal_array) == 1)
      self.assertTrue(len(p.signal_array[-1].element_array) == 2)
      self.assertTrue(self.visitor.visited_rport == 'rport')
      self.assertTrue(self.visitor.visited_signal == 'struct_signal')
      self.assertTrue(self.visitor.visited_element == 'element2')

   def test3(self):
      p = RPort('name', 'name_if')
      signal1 = ValueType('signal_type1')
      signal2 = ValueType('signal_type2')
      signal3 = StructType('signal_type3')
      signal3.add_element('element1', 'element_type1')
      signal3.add_element('element2', 'element_type2')

      p.signal_array.append(signal1.create_signal('signal1'))
      p.signal_array.append(signal2.create_signal('signal2'))
      p.signal_array.append(signal3.create_signal('signal3'))

      #print(p)
      p.accept(self.visitor)

if __name__ == '__main__':
   unittest.main()