#! /usr/bin/python
import unittest
import serial_mpg

class TestComp(unittest.TestCase):
   
   def setUp(self):
      pass

   
   def tearDown(self):
      pass 

   def test_init(self):
      x = serial_mpg.XmlParser('config/mpg.xml')
      data = x.getParsedData()
      for 
      #self.assertTrue(data == ['jog jog-counts s32'])
      
   """  
   test empty file
   test empty root
   test one line
   test wrong type
   test with mpg.xml

   """
if __name__ == '__main__':
   unittest.main()
