#include "TestHarness_c.h"
#include "simplemotion.h"
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 100

typedef struct 
{  
   char name[20];
   int baudRate;
   char opened;
   char readBuf[BUFFER_SIZE];
   char writeBuf[BUFFER_SIZE];
} portStub;

static void initStub();
static void clearWriteBuf(void);
static void clearReadBuf(void);
portStub port; 

static void initStub()
{
   memset(port.name, 0, sizeof(port.name));

   clearReadBuf();
   clearWriteBuf();

   port.opened = FALSE;
   port.baudRate = 0;
}

static void clearWriteBuf(void)
{
    memset(port.writeBuf, 0, sizeof(port.writeBuf));
}

static void clearReadBuf(void)
{
    memset(port.readBuf, 0, sizeof(port.readBuf));
}

smBusdevicePointer openCallback(const char *port_device_name, smint32 baudrate_bps, smbool *success)
{
   strcpy(port.name, port_device_name);
   port.baudRate = baudrate_bps;
   port.opened = TRUE;
   *success = TRUE;

   return &port;
}

smint32 readCallback(smBusdevicePointer busdevicePointer, unsigned char *buf, smint32 size)
{
   char str[5];

   CHECK_C(busdevicePointer == &port);

   strncpy(port.readBuf, (char *)buf, size);
   printf("readCallback: \n\tsize: %d\n\tdata: ", size);
   sprintf(str, "%d", buf[0]);
   printf("%s", str);
   printf("\n");

   return size;
}

smint32 writeCallback(smBusdevicePointer busdevicePointer, unsigned char *buf, smint32 size)
{
   char str[5];

   CHECK_C(busdevicePointer == &port);
   
   strncpy(port.writeBuf,  (char *)buf, size);

   printf("writeCallback: \n\tsize: %d\n\tdata: ", size);
   for (int i = 0; i < size; i++)
   {
      sprintf(str, "%d", port.writeBuf[i]);
      printf("%s", str);
   }
   printf("\n");

   return size;
}

void closeCallback(smBusdevicePointer busdevicePointer)
{
   CHECK_C(busdevicePointer == &port);
   port.opened = FALSE;
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

   if (dummy == 0)
   {
   }

   return smtrue;
}

TEST_GROUP_C_SETUP(DriverTestGroup)
{
   initStub();
}

TEST_GROUP_C_TEARDOWN(DriverTestGroup)
{
}

TEST_C(DriverTestGroup, openBus)
{
   smbus bus = smOpenBusWithCallbacks("COM1", openCallback, closeCallback, readCallback, writeCallback, purgeCallback);

   CHECK_C(strcmp(port.name, "COM1") == 0);
   CHECK_C(bus != -1);
   CHECK_C(port.opened);
}


TEST_C(DriverTestGroup, openCloseBus)
{
   smbus bus = smOpenBusWithCallbacks("COM2", openCallback, closeCallback, readCallback, writeCallback, purgeCallback);

   CHECK_C(strcmp(port.name, "COM2") == 0);
   CHECK_C(bus != -1);
   CHECK_C(port.opened);

   CHECK_C(smCloseBus( bus ) == SM_OK);
   CHECK_C(!port.opened);
}

TEST_C(DriverTestGroup, sendMsg)
{
   smint32 paramVal1 = 0;
   SM_STATUS status;

   smbus bus = smOpenBusWithCallbacks("COM1", openCallback, closeCallback, readCallback, writeCallback, purgeCallback);

//SM_STATUS smRead1Parameter( const smbus handle, const smaddr nodeAddress, const smint16 paramId1, smint32 *paramVal1 );
   status = smRead1Parameter( bus, 254, 1,  &paramVal1);

   CHECK_C(status == SM_OK);
}