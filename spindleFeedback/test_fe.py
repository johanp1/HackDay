#! /usr/bin/python
import unittest
import fake_encoder
import comms  

class TestComp(unittest.TestCase):
      
   def setUp(self):
      self.fake = fake_encoder.FakeEncoder(0.05, 500)
      self.HalAdapter = fake_encoder.HalAdapter('fake-encoder', self.fake.clear)
         
   def test_init(self):
      self.assertTrue(self.fake.position == 0)
      self.assertTrue(self.fake.velocity == 0)   
      self.assertTrue(self.fake.dT == 0.05)
      self.assertTrue(self.fake.scale == 500)
      
      self.assertTrue(self.HalAdapter.h.name == 'fake-encoder')
      
      self.assertTrue(self.HalAdapter.h['velocity'] == 0)
      self.assertTrue(self.HalAdapter.h.pinDict['velocity'].type == 'HAL_FLOAT')
      self.assertTrue(self.HalAdapter.h.pinDict['velocity'].dir == 'HAL_OUT')
      self.assertTrue(self.HalAdapter.h['position'] == 0)
      self.assertTrue(self.HalAdapter.h.pinDict['position'].type == 'HAL_FLOAT')
      self.assertTrue(self.HalAdapter.h.pinDict['position'].dir == 'HAL_OUT')
      self.assertTrue(self.HalAdapter.h['index-enable'] == 0)
      self.assertTrue(self.HalAdapter.h.pinDict['index-enable'].type == 'HAL_BIT')
      self.assertTrue(self.HalAdapter.h.pinDict['index-enable'].dir == 'HAL_IO')
      self.assertTrue(self.HalAdapter.h.readyFlag == 1)

   def test_handleEvent(self):
      pos = 100.0 # => vel = pos/dt/scale = pos/(dt*scale) => 100/25 = 4
      self.fake.handleEvent('pos', str(int(pos)))

      expectedVel = round(float(pos/25), 3)
      encoderVel = round(self.fake.velocity, 3)
      
      expectedPos = round(pos/500, 3)
      encoderPos = round(self.fake.position, 3)
      
      self.assertTrue(encoderPos == expectedPos)
      self.assertTrue(encoderVel == expectedVel)   

      self.HalAdapter.update(self.fake.velocity, self.fake.position)
      halPos = round(self.HalAdapter.h['position'], 3)
      halVel = round(self.HalAdapter.h['velocity'], 3)
      self.assertTrue(halVel == expectedVel)
      self.assertTrue(halPos == expectedPos)

   def test_handleMultipleEvents(self):
      pos = 60.0 #actual encoder pulses in 0.05s interval 
      self.fake.handleEvent('pos', str(int(pos)))
      expectedVel = round(float(60.0/25), 3)
      encoderVel = round(self.fake.velocity, 3)
      expectedPos = round(pos/500, 3)
      encoderPos = round(self.fake.position, 3)
      
      self.assertTrue(encoderPos == expectedPos)
      self.assertTrue(encoderVel == expectedVel)   

      self.HalAdapter.update(self.fake.velocity, self.fake.position)
      halPos = round(self.HalAdapter.h['position'], 3)
      halVel = round(self.HalAdapter.h['velocity'], 3)
      self.assertTrue(halVel == expectedVel)
      self.assertTrue(halPos == expectedPos)   

      self.fake.handleEvent('pos', str(int(pos)))
      expectedVel = round(float(60.0/25), 3)
      encoderVel = round(self.fake.velocity, 3)
      expectedPos = expectedPos + round(pos/500, 3)
      encoderPos = round(self.fake.position, 3)

      self.assertTrue(encoderPos == expectedPos)
      self.assertTrue(encoderVel == expectedVel)   

      self.HalAdapter.update(self.fake.velocity, self.fake.position)
      halPos = round(self.HalAdapter.h['position'], 3)
      halVel = round(self.HalAdapter.h['velocity'], 3)
      self.assertTrue(halVel == expectedVel)
      self.assertTrue(halPos == expectedPos)   

   def test_wrongEvent(self):
      self.fake.handleEvent('apa', '1000')

      self.assertTrue(self.fake.position == 0)
      self.assertTrue(self.fake.velocity == 0)   

   def test_clear(self):
      self.fake.handleEvent('pos', '2000')
      self.fake.clear()

      self.assertTrue(self.fake.position == 0)  

   def test_setIndexEnable(self):
      pos = 600.0
      self.fake.handleEvent('pos', str(int(pos)))

      expectedVel = round(pos/25, 3)
      encoderVel = round(self.fake.velocity, 3)
      
      expectedPos = round(pos/500, 3)
      encoderPos = round(self.fake.position, 3)
      
      self.assertTrue(encoderPos == expectedPos)
      self.assertTrue(encoderVel == expectedVel)   
      
      self.HalAdapter.update(self.fake.velocity, self.fake.position)
      halPos = round(self.HalAdapter.h['position'], 3)
      halVel = round(self.HalAdapter.h['velocity'], 3)
      self.assertTrue(halVel == expectedVel)
      self.assertTrue(halPos == expectedPos)

      self.HalAdapter.h['index-enable'] = 1
      self.HalAdapter.update(self.fake.velocity, self.fake.position)

      self.assertTrue(self.fake.position == 0)  
      #self.assertTrue(self.fake.count == 0)
      self.assertTrue(self.HalAdapter.h['position'] == 0)
      self.assertTrue(self.HalAdapter.h['index-enable'] == 0)


if __name__ == '__main__':
   unittest.main()