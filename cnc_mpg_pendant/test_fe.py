#! /usr/bin/python
import unittest
import fake_encoder
import comms  

class TestComp(unittest.TestCase):
      
   def setUp(self):
      self.fake = fake_encoder.FakeEncoder(500)
      self.halFacade = fake_encoder.HalFacade('fake-encoder', self.fake.clear)
         
   def test_init(self):
      self.assertTrue(self.fake.position == 0)
      self.assertTrue(self.fake.velocity == 0)   
      self.assertTrue(self.fake.count == 0)
      self.assertTrue(self.fake.scale == 500)

      self.assertTrue(self.halFacade.h.name == 'fake-encoder')
      
      self.assertTrue(self.halFacade.h['velocity'] == 0)
      self.assertTrue(self.halFacade.h.pinDict['velocity'].type == 'HAL_FLOAT')
      self.assertTrue(self.halFacade.h.pinDict['velocity'].dir == 'HAL_OUT')
      self.assertTrue(self.halFacade.h['position'] == 0)
      self.assertTrue(self.halFacade.h.pinDict['position'].type == 'HAL_FLOAT')
      self.assertTrue(self.halFacade.h.pinDict['position'].dir == 'HAL_OUT')
      self.assertTrue(self.halFacade.h['index-enable'] == 0)
      self.assertTrue(self.halFacade.h.pinDict['index-enable'].type == 'HAL_BIT')
      self.assertTrue(self.halFacade.h.pinDict['index-enable'].dir == 'HAL_IO')
      self.assertTrue(self.halFacade.h.ready_flag == 1)

   def test_handleEvent(self):
      self.fake.handleEvent(comms.Event('rpm', '12'))

      self.assertTrue(self.fake.position == 12/500)
      self.assertTrue(self.fake.velocity == 12/60)   
      self.assertTrue(self.fake.count == 12)

      self.halFacade.update(self.fake.velocity, self.fake.position)
      self.assertTrue(self.halFacade.h['velocity'] == 12/60)
      self.assertTrue(self.halFacade.h['position'] == 12/500)

   def test_wrongEvent(self):
      self.fake.handleEvent(comms.Event('apa', '1000'))

      self.assertTrue(self.fake.position == 0)
      self.assertTrue(self.fake.velocity == 0)   
      self.assertTrue(self.fake.count == 0)

   def test_clear(self):
      self.fake.handleEvent(comms.Event('rpm', '120'))
      self.fake.clear()

      self.assertTrue(self.fake.position == 0)  
      self.assertTrue(self.fake.count == 0)

   def test_setIndexEnable(self):
      self.fake.handleEvent(comms.Event('rpm', '500'))

      self.assertTrue(self.fake.position == 1)
      self.assertTrue(self.fake.velocity == 500/60)   
      self.assertTrue(self.fake.count == 500)

      self.halFacade.update(self.fake.velocity, self.fake.position)
      self.assertTrue(self.halFacade.h['velocity'] == 500/60)
      self.assertTrue(self.halFacade.h['position'] == 1)

      self.halFacade.h['index-enable'] = 1
      self.halFacade.update(self.fake.velocity, self.fake.position)

      self.assertTrue(self.fake.position == 0)  
      self.assertTrue(self.fake.count == 0)
      self.assertTrue(self.halFacade.h['position'] == 0)
      self.assertTrue(self.halFacade.h['index-enable'] == 0)



if __name__ == '__main__':
   unittest.main()