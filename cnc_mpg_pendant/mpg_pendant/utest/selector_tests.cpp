#include "TestHarness.h"
#include "selector.h"
#include "Arduino.h"

#define PIN 2

TEST_GROUP(SelectorTestGroup)
{
  class eventListnerSpy : public C_EventListner{
  public:
    void enventListnerSpy()
    {
      reset();
    };
    
    void handleEvent(C_Event& e)
    {
      eventData = e.getData();
      eventSource = e.getSource();
      newData = true;
    };

    void reset()
    {
      eventData = 0;
      eventSource = "";
      newData = false;
    }
    
    unsigned int eventData;
    string eventSource;
    bool newData;
  };

  
  C_Selector* s;
  eventListnerSpy evSpy;
  
  void setup()
  {
    ArduinoStub.reset();
    evSpy.reset();
    s = new C_Selector("test", PIN, 100);
    s->addEventListner(&evSpy);
  }
  
  void teardown()
  {
    delete s;
  }

};

TEST(SelectorTestGroup, Init)
{
  LONGS_EQUAL(0, s->getState());
}

TEST(SelectorTestGroup, SteadyState)
{
  ArduinoStub.setAnalogRead(PIN, 0);

  s->scan();
  LONGS_EQUAL(0, s->getState());
  
  ArduinoStub.incTime(101); //longer than debounce delay

  s->scan();
  LONGS_EQUAL(0, s->getState());
}

/*
TEST(SelectorTestGroup, ButtonNotPressed)
{
  ArduinoStub.setDigitalRead(PIN, LOW);
  
  b->scan();
  LONGS_EQUAL(LOW, b->getState());
  CHECK(!evSpy.newData);
  
  ArduinoStub.incTime(51); //longer than debounce delay
  
  b->scan();
  LONGS_EQUAL(LOW, b->getState());
  CHECK(!evSpy.newData);
}

TEST(SelectorTestGroup, PressButtonLong)
{
  ArduinoStub.setDigitalRead(PIN, HIGH);

  b->scan();
  LONGS_EQUAL(LOW, b->getState());
  CHECK(!evSpy.newData);
  
  ArduinoStub.incTime(51); //longer than debounce delay
  
  b->scan();
  LONGS_EQUAL(HIGH, b->getState());
  CHECK(evSpy.newData);
  LONGS_EQUAL(1, evSpy.eventData);
  CHECK(evSpy.eventSource.compare("test") == 0);
}

TEST(SelectorTestGroup, PressButtonShort)
{
  ArduinoStub.setDigitalRead(PIN, HIGH);

  b->scan();
  LONGS_EQUAL(LOW, b->getState());
  CHECK(!evSpy.newData);
    
  ArduinoStub.incTime(49); //shorter than debounce delay
  
  b->scan();
  LONGS_EQUAL(LOW, b->getState());
  CHECK(!evSpy.newData);
}

TEST(SelectorTestGroup, ReleaseButton)
{
  ArduinoStub.setDigitalRead(PIN, HIGH);

  b->scan();

  ArduinoStub.incTime(51); //longer than debounce delay

  b->scan();
  LONGS_EQUAL(HIGH, b->getState());

  ArduinoStub.setDigitalRead(PIN, LOW);

  b->scan();
  LONGS_EQUAL(HIGH, b->getState());
  
  ArduinoStub.incTime(51); //longer than debounce delay

  b->scan();
  LONGS_EQUAL(LOW, b->getState());
}
*/
