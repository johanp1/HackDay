#include "TestHarness.h"
#include "sender.h"

TEST_GROUP(SenderTestGroup)
{
   C_Sender s;
  
   void setup()
   {  
      ArduinoStub.reset();
   }
  
   void teardown()
   {
   }
};

TEST(SenderTestGroup, SendEvent)
{
  string evName = string("bepa");
  string expected = string("bepa_123\n");
  C_Event e = C_Event(evName, 123);
  s.sendEvent(e);
  //CHECK(ArduinoStub.getSerialBuffer().compare(expected) == 0);
}
/*
TEST(SenderTestGroup, HandleEvent)
{
  string evName = string("apa");
  string expected = string("apa_321\n");
  C_Event e = C_Event(evName, 321);
  s.handleEvent(e);
  CHECK(ArduinoStub.getSerialBuffer().compare(expected) == 0);
}
*/
