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
      serializedEvent = String("");
    };
    
    void handleEvent(C_Event& e)
    {
      serializedEvent = e.serialize();
    };
   
    String serializedEvent;
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
