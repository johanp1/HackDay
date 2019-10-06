#include "TestHarness.h"
#include "event_generator.h"
#include "event_listner.h"
#include "event.h"

TEST_GROUP(EventGeneratorTestGroup)
{
  class eventListnerSpy : public C_EventListner{
  public:
    void enventListnerSpy()
    {
      //      eventData = 0;
      serializedEvent = "";
    };
    
    void handleEvent(C_Event& e)
    {
      //eventData = e.getData();
      //eventSource = e.getSource();
      serializedEvent = e.serialize();
    };
    
    //    unsigned int eventData;
    //string eventSource;
    string serializedEvent;
  };
  
  C_EventGenerator* eg;
  eventListnerSpy evSpy;
  
  void setup()
  {
    eg = new C_EventGenerator("test");
    eg->addEventListner(&evSpy);
  }
  
  void teardown()
  {
    delete eg;
  }

};


TEST(EventGeneratorTestGroup, CheckWhenNoEvent)
{
  CHECK(evSpy.serializedEvent.compare("") == 0);
}


TEST(EventGeneratorTestGroup, GenerateEvent)
{
  eg->generateEvent(100);
  CHECK(evSpy.serializedEvent.compare("test_100") == 0);
}

