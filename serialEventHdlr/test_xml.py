#! /usr/bin/python
import unittest
import serialEventHandler as eh
import os

class TestXml(unittest.TestCase):
   def createTestFile(self):
      """creates a test xml-file with an empty root"""
      self.f = open('test.xml','w')
      self.f.write("<mpg>\n"\
                   "</mpg>")
      self.f.close()
      
   def addTestPin(self, pinName, pinEvent, pinType, pinDirection = 'out'):
      f = open('test.xml', 'r')
      contents = f.readlines()
      f.close()

      str = '\t<test>\n\t\t<halpin>\"' + pinName + '\"<event>' + pinEvent + '</event><type>' +  pinType + '</type><direction>' +  pinDirection + '</direction></halpin>\n\t</test>\n'
      
      contents.insert(-1, str)

      f = open('test.xml', 'w')
      contents = "".join(contents)
      f.write(contents)
      f.close()
   
   def setUp(self):
      self.f = self.createTestFile()
   
   def tearDown(self): 
      os.remove("test.xml")

   def test_empty(self):
      x = eh.XmlParser('test.xml')
      data = x.get_parsed_data()
      self.assertTrue(len(data) == 0)

   def test_unsupportedPinType(self):
      self.addTestPin('jog_pin', 'jog', 'x32')
      
      x = eh.XmlParser('test.xml')
      data = x.get_parsed_data()
      self.assertTrue(len(data) == 0)

   def test_unsupportedPinDirection(self):
      self.addTestPin('jog_pin', 'jog', 'u32', 'iut')
      
      x = eh.XmlParser('test.xml')
      data = x.get_parsed_data()
      self.assertTrue(len(data) == 0)

   def test_onePin(self):
      self.addTestPin('jog_pin', 'jog', 'u32')
      
      x = eh.XmlParser('test.xml')
      data = x.get_parsed_data()
      self.assertTrue(len(data) == 1)
      
      self.assertTrue(data[0].name == 'jog_pin')
      self.assertTrue(data[0].type == 'u32')
      self.assertTrue(data[0].direction == 'out')

   def test_twoPin(self):
      self.addTestPin('jog_pin', 'jog', 'u32')
      self.addTestPin('rth_pin', 'rth', 'bit', 'in')
      
      x = eh.XmlParser('test.xml')
      data = x.get_parsed_data()
      self.assertTrue(len(data) == 2)
      
      self.assertTrue(data[0].name == 'jog_pin')
      self.assertTrue(data[0].type == 'u32')
      self.assertTrue(data[0].direction == 'out')
      self.assertTrue(data[1].name == 'rth_pin')
      self.assertTrue(data[1].type == 'bit')
      self.assertTrue(data[1].direction == 'in')

   """  
   test empty file
   test empty root
   test one line
   test wrong type
   test with mpg.xml

   """
if __name__ == '__main__':
   unittest.main()
