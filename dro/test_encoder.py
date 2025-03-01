import RPi.GPIO as GPIO
import unittest
import encoder 

class TestEncoder(unittest.TestCase):
  def setUp(self):
    self.encoder = encoder.Encoder()

  def test_encoder(self):
    self.assertTrue(GPIO.BOARD == 0)
    self.assertTrue(GPIO.IN == 0)
    self.assertTrue(GPIO.OUT == 1)
    self.assertTrue(self.encoder.pos == 0)

  def test_cc(self):
    self.encoder.update()
    self.assertTrue(self.encoder.pos == 1)

#  def test_cc(self):
#    self.encoder.update()
#    self.assertTrue(self.encoder.pos == -1)

if __name__ == '__main__':
   unittest.main()