#include <gtest/gtest.h>
#include "sender.h"
#include "Arduino.h"
namespace {
class SenderTestFixture : public testing::Test 
{
   protected: 
   Sender s;
  
   void setup()
   {  
      Serial.clear();
   }
  
   void teardown()
   {
   }
};

TEST_F(SenderTestFixture, SendEvent)
{
   String sendStr = String("bepa_123");
   string expected = string("bepa_123\n");
   
   s.send(sendStr);
   ASSERT_TRUE(Serial.getData().compare(expected) == 0);
}

TEST_F(SenderTestFixture, HandleEvent)
{
  String evSource = String("apa");
   string expected = string("apa_321\n");
   C_Event e = C_Event(evSource, 321);
   
   s.HandleEvent(e);
   ASSERT_TRUE(Serial.getData().compare(expected) == 0);
}
} // namespace
