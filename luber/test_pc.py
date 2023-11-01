#! /usr/bin/python
import unittest
import luber  
import subprocess
import filecmp
import xml.etree.ElementTree as ET

class TestXml(unittest.TestCase):
   def createTestFile(self):
      """creates a test xml-file with an empty root"""
      self.testFile = 'test.xml'
      self.f = open(self.testFile,'w')
      self.f.write("<luber>\n"\
                    "</luber>")
      self.f.close()

   def addTestPar(self, fileName, parName, value):
      f = open(fileName, 'r')
      contents = f.readlines()
      f.close()

      str = '\t<parameter name=' + '"' + parName + '"' + ' value=' + '"' + value + '"' + ' />\n'
      contents.insert(-1, str)

      f = open(fileName, 'w')
      contents = "".join(contents)
      f.write(contents)
      f.close()
    
   def setUp(self):
      #subprocess.call("rm test.xml", shell=True) 
      self.f = self.createTestFile()

    
   def tearDown(self):
      callString = "rm " + self.testFile 
      subprocess.call(callString, shell=True) 

   def test_empty(self):
      x = luber.ParameterContainer('test.xml')
      data = x.get_params()
      self.assertTrue(len(data) == 0)

   def test_unsupportedPinType(self):
      self.addTestPar(self.testFile, 'par1', '0.0')
        
      x = luber.ParameterContainer(self.testFile)
      data = x.get_param('par2')
      self.assertTrue(data == None)

   def test_onePar(self):
      self.addTestPar(self.testFile, 'par1', '1.0')
      
      x = luber.ParameterContainer(self.testFile)
      data = x.get_param('par1')
      self.assertTrue(data == 1.0)

   def test_writePar(self):
      self.addTestPar(self.testFile, 'par1', '1.0')
     
      x = luber.ParameterContainer(self.testFile)
      data = x.get_param('par1')
      self.assertTrue(data == 1.0)

      x.write_param('par1', 2.6)
      data = x.get_param('par1')
      self.assertTrue(data == 2.6)

   def test_write2Par(self):
      self.addTestPar(self.testFile, 'par1', '1.0')
      self.addTestPar(self.testFile, 'par2', '2.0')

      x = luber.ParameterContainer(self.testFile)
      data = x.get_param('par2')
      self.assertTrue(data == 2.0)

      x.write_param('par2', 2.1)
      data = x.get_param('par2')
      self.assertTrue(data == 2.1)
      data = x.get_param('par1')
      self.assertTrue(data == 1.0)

   def test_writeToFile(self):
      self.addTestPar(self.testFile, 'par1', '1.0')
      self.addTestPar(self.testFile, 'par2', '200.4')

      x = luber.ParameterContainer(self.testFile)
      x.write_param('par1', 100.4)
      x.write_to_file()

      tree = ET.parse(self.testFile)
      root = tree.getroot()
      for param in root.iter('parameter'):
         if param.attrib['name'] == 'par1':
            self.assertTrue(param.attrib['value'] == '100.4')

         if param.attrib['name'] == 'par2':
            self.assertTrue(param.attrib['value'] == '200.4')


if __name__ == '__main__':
   unittest.main()
