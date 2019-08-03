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
   C_Event e = C_Event((string)"bepa", 123);
	s.sendEvent(e);
   CHECK(ArduinoStub.getSerialBuffer().compare((string)"bepa_123\n") == 0);
}

TEST(SenderTestGroup, HandleEvent)
{
   C_Event e = C_Event((string)"apa", 321);
   s.handleEvent(e);
   CHECK(ArduinoStub.getSerialBuffer().compare((string)"apa_321\n") == 0);
}