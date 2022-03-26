#! /usr/bin/python

import unittest
from ArxmlParser import RPort
from ArxmlParser import PPort

class TestPort(unittest.TestCase):
   def test_init_pport(self):
      p = RPort('port_name', 'port_if')
            
      self.assertTrue(p.port_name == 'port_name')
      self.assertTrue(p.port_if == 'port_if')
      self.assertTrue(p.direction == 'required')

   def test_init_rport(self):
      p = PPort('port_name', 'port_if')
            
      self.assertTrue(p.port_name == 'port_name')
      self.assertTrue(p.port_if == 'port_if')
      self.assertTrue(p.direction == 'provided')

if __name__ == '__main__':
   unittest.main()