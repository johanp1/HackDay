#include "TestHarness.h"
#include "sender.h"

TEST_GROUP(SenderTestGroup)
{
   C_Sender s;
  
   void setup()
   {  
      Serial.clear();
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
   CHECK(Serial.getData().compare(expected) == 0);
}

TEST(SenderTestGroup, HandleEvent)
{
   string evName = string("apa");
   string expected = string("apa_321\n");
   C_Event e = C_Event(evName, 321);
   
   s.handleEvent(e);
   CHECK(Serial.getData().compare(expected) == 0);
}

