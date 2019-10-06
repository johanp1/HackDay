#include "TestHarness.h"
#include "sender.h"
#include "Arduino.h"
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
   string sendStr = string("bepa_123");
   string expected = string("bepa_123\n");
   
   s.send(sendStr);
   CHECK(Serial.getData().compare(expected) == 0);
}

TEST(SenderTestGroup, handleEvent)
{
  string evSource = string("apa");
   string expected = string("apa_321\n");
   C_Event e = C_Event(evSource, 321);
   
   s.handleEvent(e);
   CHECK(Serial.getData().compare(expected) == 0);
}

