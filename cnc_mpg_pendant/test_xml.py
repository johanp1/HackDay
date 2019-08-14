#! /usr/bin/python
import unittest
import serial_mpg
#import comms  
import subprocess

class TestComp(unittest.TestCase):
   def createTestFile(self):
      """creates a test xml-file with an empty root"""
      self.f = open('test.xml','w')
      self.f.write("<mpg>\n"\
                   "</mpg>")
      self.f.close()

      
   def addTestPin(self, pinName, pinEvent, pinType):
      f = open('test.xml', 'r')
      contents = f.readlines()
      f.close()

      str = '\t<test>\n\t\t<halpin>\"' + pinName + '\"<event>' + pinEvent + '</event><type>' +  pinType + '</type></halpin>\n\t</test>\n'
      contents.insert(-1, str)

      f = open('test.xml', 'w')
      contents = "".join(contents)
      f.write(contents)
      f.close()
   
   def setUp(self):
      #subprocess.call("rm test.xml", shell=True) 
      self.f = self.createTestFile()

   
   def tearDown(self):
      subprocess.call("rm test.xml", shell=True) 

   def test_empty(self):
      x = serial_mpg.XmlParser('test.xml')
      data = x.getParsedData()
      self.assertTrue(len(data) == 0)

   def test_unsupportedPinType(self):
      self.addTestPin('jog_pin', 'jog', 'x32')
      
      x = serial_mpg.XmlParser('test.xml')
      data = x.getParsedData()
      self.assertTrue(len(data) == 0)

   def test_onePin(self):
      self.addTestPin('jog_pin', 'jog', 'u32')
      
      x = serial_mpg.XmlParser('test.xml')
      data = x.getParsedData()
      self.assertTrue(len(data) == 1)
      self.assertTrue(data['jog'].name == 'jog_pin')
      self.assertTrue(data['jog'].type == 'u32')

   def test_twoPin(self):
      self.addTestPin('jog_pin', 'jog', 'u32')
      self.addTestPin('rth_pin', 'rth', 'bit')
      
      x = serial_mpg.XmlParser('test.xml')
      data = x.getParsedData()
      self.assertTrue(len(data) == 2)
      self.assertTrue(data['jog'].name == 'jog_pin')
      self.assertTrue(data['jog'].type == 'u32')
      self.assertTrue(data['rth'].name == 'rth_pin')
      self.assertTrue(data['rth'].type == 'bit')
      
   """  
   test empty file
   test empty root
   test one line
   test wrong type
   test with mpg.xml

   """
if __name__ == '__main__':
   unittest.main()
