#include "TestHarness.h"
#include "receiver.h"
#include "Arduino.h"

TEST_GROUP(ReceiverTestGroup)
{
   class EventListnerSpy : public EventListner{
   public:
      void enventListnerSpy()
      {
         reset();
      };
    
      void handleEvent(C_Event& e)
      {
         serializedEvent = e.serialize();
         newData = true;
      };

      void reset()
      {
         serializedEvent = String("");
         newData = false;
      };
      
      String serializedEvent;
      bool newData;
   };

   Receiver r = Receiver("test");
   EventListnerSpy evSpy;
  
   void checkEvent(string& expected)
   {
      CHECK(evSpy.newData);
      CHECK(evSpy.serializedEvent.compare(expected) == 0);
   }

   void setup()
   {
      ArduinoStub.reset();
      evSpy.reset();
      r.addEventListner(&evSpy);
   }
   
   void teardown()
   {
      Serial.clear();
   }
};

TEST(ReceiverTestGroup, ScanEmptyRecBuf)
{
   r.scan();
   CHECK(!evSpy.newData);
}

TEST(ReceiverTestGroup, ScanOneMsgRec)
{
   String str = "12";
   Serial.putData(str);
   r.scan();
   CHECK(evSpy.newData);
   CHECK(evSpy.serializedEvent.compare("test_12") == 0);
}
