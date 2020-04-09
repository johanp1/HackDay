#include "TestHarness.h"
#include "time_server.h"
#include "Arduino.h"


TEST_GROUP(TimeServerTestGroup)
{
   class EventListnerSpy : public EventListner{
   public:
      void enventListnerSpy()
      {
         reset();
      };
    
      void handleEvent(C_Event& e)
      {
         newData = true;
         serializedEvent = e.serialize();
      };

      void reset()
      {
         serializedEvent = "";
         newData = false;
      }
    
      String serializedEvent;
      bool newData;
   };

   TimeServer* t;
   EventListnerSpy evSpy;
  
   void setup()
   {
      ArduinoStub.reset();
      t = new TimeServer("test", 50);
      t->addEventListner(&evSpy);
   }
  
   void teardown()
   {
      delete t;
   }

};

TEST(TimeServerTestGroup, TestInitiated)
{
   CHECK(!evSpy.newData);
}

TEST(TimeServerTestGroup, TestGenerateEvent)
{
   // call isr
   //CHECK(evSpy.newData);
   //CHECK(evSpy.serializedEvent.compare("test_1") == 0);
}