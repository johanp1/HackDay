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
      eventData = 0;
      eventSource = "";
    };
    
    void handleEvent(C_Event& e)
    {
      eventData = e.getData();
      eventSource = e.getSource();
    };
    
    unsigned int eventData;
    string eventSource;
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
  LONGS_EQUAL(0, evSpy.eventData);
}


TEST(EventGeneratorTestGroup, GenerateEvent)
{
  eg->generateEvent(100);
  LONGS_EQUAL(100, evSpy.eventData);
  CHECK(evSpy.eventSource.compare("test") == 0);
}

