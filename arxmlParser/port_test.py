#! /usr/bin/python

import unittest
from ArxmlParser import RPort, PPort, ValueSignal, StructSignal, StructSignalElement

class TestVisitor:
   def __init__(self):
      self.pport_rendered = False
      self.rport_rendered = False

   def renderPPort(self, port):
      self.pport_rendered = True

   def renderRPort(self, port):
      self.rport_rendered = True

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
      self.assertTrue(self.visitor.pport_rendered)
      self.assertFalse(self.visitor.rport_rendered)
      
   def test_visit_rport(self):
      p = RPort('test_rport', 'rport_if')

      p.accept(self.visitor)
      self.assertFalse(self.visitor.pport_rendered)
      self.assertTrue(self.visitor.rport_rendered)

if __name__ == '__main__':
   unittest.main()