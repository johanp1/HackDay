#include "TestHarness_c.h"
#include "simplemotion.h"

#define TRUE 1
#define FALSE 0


      char hasBeenCalled = FALSE;
      int baudRate = 90;
      int busHandle = 123;

      smBusdevicePointer openCallback(const char *port_device_name, smint32 baudrate_bps, smbool *success)
      {
         if(port_device_name[0] == 'C')
         {
         }
      
         baudRate = baudrate_bps;
         hasBeenCalled = TRUE;
         *success = TRUE;
      
         return &busHandle;
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
         if (dummy == 0) {}
      
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
         if (dummy == 0) {}
         
         return 0;
      }

      void closeCallback(smBusdevicePointer busdevicePointer)
      {
         int dummy = 0;
         
         if (busdevicePointer == 0)
            dummy = 1;
         if (dummy == 0) {}
      }

      smbool purgeCallback(smBusdevicePointer busdevicePointer, BusDeviceMiscOperationType operation)
      {
         int dummy = 0;
         
         if (busdevicePointer == 0)
            dummy = 1;
         if (operation == MiscOperationFlushTX)
            dummy = 2;
         else
            dummy = 3;
         
         if (dummy == 0) {}
         
         return smtrue;
      }
   

TEST_GROUP_C_SETUP(DriverTestGroup)
{
}
  
TEST_GROUP_C_TEARDOWN(DriverTestGroup)
{
}

TEST_C(DriverTestGroup, openBus)
{
   //BusdeviceOpen openBusCallback = &(serial.openCallback);

   smbus bus = smOpenBusWithCallbacks("COM1", openCallback, 0, 0, 0 , 0);
   //smbus bus = smOpenBusWithCallbacks("COM1", openCallback, closeCallback, readCallback, writeCallback , purgeCallback);

   if (bus == 0) {}

  CHECK_C(hasBeenCalled);
}