#include "TestHarness.h"
#include "button.h"
#include "Arduino.h"

#define PIN 3

TEST_GROUP(ButtonTestGroup)
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

  
  C_Button* b;
  eventListnerSpy evSpy;
  
  void setup()
  {
    ArduinoStub.reset();
    b = new C_Button("test", PIN, 50);
    b->addEventListner(&evSpy);
  }
  
  void teardown()
  {
    delete b;
  }

};

TEST(ButtonTestGroup, Init)
{
  LONGS_EQUAL(INPUT, ArduinoStub.getMode(PIN));
  LONGS_EQUAL(LOW, b->getState());
}

TEST(ButtonTestGroup, ButtonNotPressed)
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

TEST(ButtonTestGroup, PressButtonLong)
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

TEST(ButtonTestGroup, PressButtonShort)
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

TEST(ButtonTestGroup, ReleaseButton)
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

