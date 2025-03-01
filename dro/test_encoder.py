#import RPi.GPIO as GPIO
import RPi
import unittest
import encoder 

class TestEncoder(unittest.TestCase):
  def setUp(self):
    self.encoder = encoder.Encoder()

  def test_encoder(self):
    self.assertTrue(RPi.GPIO.BOARD == 0)
    self.assertTrue(RPi.GPIO.IN == 0)
    self.assertTrue(RPi.GPIO.OUT == 1)

    self.assertTrue(self.encoder.pos == 0)
    self.encoder.update()
    self.assertTrue(self.encoder.pos == 1)

if __name__ == '__main__':
   unittest.main()