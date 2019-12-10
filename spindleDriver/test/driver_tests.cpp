#include "TestHarness.h"
#include "simplemotion.h"

TEST_GROUP(DriverTestGroup)
{
  smbus bus;
  bool hasBeenCalled = FALSE;
  int baudRate = 0;
  
  int busHandle = 123;
  
  void setup()
  {  
  }
  
  void teardown()
  {
//    buffer.flush();
  }

   smBusdevicePointer openCallback(const char *port_device_name, smint32 baudrate_bps, smbool *success)
   {
      if(port_device_name[0] == 'C')
      {
      }
      
      baudRate = baudrate_bps;
      hasBeenCalled = TRUE;
      *success = TRUE;
      
      return &dusHandle;
   }
  
   smint32 readCallback(smBusdevicePointer busdevicePointer, unsigned char *buf, smint32 size)
   {
      int dummy = 0;
      
      if (busdevicePointer == 0)
         dummy = 1;
      if (buf == 0)
         dummy = 2;
      if (size == 0)
         dummy = 3;
      
      return 0;
   }

   smint32 writeCallback(smBusdevicePointer busdevicePointer, unsigned char *buf, smint32 size)
   {
      int dummy = 0;
      
      if (busdevicePointer == 0)
         dummy = 1;
      if (buf == 0)
         dummy = 2;
      if (size == 0)
         dummy = 3;
      
      return 0;
   }

   void closeCallback(smBusdevicePointer busdevicePointer)
   {
      int dummy = 0;
      
      if (busdevicePointer == 0)
         dummy = 1;
   }

   smbool purgeCallback(smBusdevicePointer busdevicePointer, BusDeviceMiscOperationType operation)
   {
   }
};

TEST(BufferTestGroup, openBus)
{
   bus = smOpenBusWithCallbacks("COM1", openCallback, closeCallback, readCallback, writeCallback , purgeCallback);

  CHECK(hasBeenCalled);
}