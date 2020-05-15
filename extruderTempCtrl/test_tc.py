#! /usr/bin/python
import unittest
import hal_exruder_temp_ctrl

class TestComp(unittest.TestCase):
   def setUp(self):
      self.tempCtrler = hal_exruder_temp_ctrl.TempControllerFacade('dummy')
      self.tempCtrler.tempController.serial.reset()

   def test_init(self):
      self.assertTrue(self.tempCtrler.currTemp == 100)
      self.assertTrue(self.tempCtrler.refTemp == 100)
      self.assertTrue(self.tempCtrler.enable == False)

   def test_setTempDisable(self):
      self.tempCtrler.setRefTemp(200)
      self.assertTrue(self.tempCtrler.tempController.serial.writeBuf == '')

   def test_setEnable(self):
      self.tempCtrler.setEnable(True)
      self.assertTrue(self.tempCtrler.enable)

   def test_setTemp(self):
      self.tempCtrler.setEnable(True)
      self.tempCtrler.setRefTemp(200)
      self.assertTrue(self.tempCtrler.tempController.serial.writeBuf == 'sp_200\n')

if __name__ == '__main__':
   unittest.main()