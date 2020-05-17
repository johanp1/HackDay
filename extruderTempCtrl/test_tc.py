#! /usr/bin/python
import unittest
import comms
import hal_exruder_temp_ctrl

class TestComp(unittest.TestCase):
   def setUp(self):
      self.tempCtrler = hal_exruder_temp_ctrl.TempControllerFacade('dummy')
      self.tempCtrler.tempController.serial.reset()

   def test_init(self):
      self.assertTrue(self.tempCtrler.currTemp == 100)
      self.assertTrue(self.tempCtrler.refTemp == 100)
      self.assertFalse(self.tempCtrler.enable)

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

   def test_getCurrTemp(self):
      # send a message. i.e call the registered callbak with the "received" message
      self.tempCtrler.tempController.msg_hdlr(comms.Message('mv', '123'))
      self.assertTrue(self.tempCtrler.currTemp == 123)

if __name__ == '__main__':
   unittest.main()