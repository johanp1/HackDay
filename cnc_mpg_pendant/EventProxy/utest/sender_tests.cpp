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
   String sendStr = String("bepa_123");
   string expected = string("bepa_123\n");
   
   s.send(sendStr);
   CHECK(Serial.getData().compare(expected) == 0);
}

TEST(SenderTestGroup, handleEvent)
{
  String evSource = String("apa");
   string expected = string("apa_321\n");
   C_Event e = C_Event(evSource, 321);
   
   s.handleEvent(e);
   CHECK(Serial.getData().compare(expected) == 0);
}

