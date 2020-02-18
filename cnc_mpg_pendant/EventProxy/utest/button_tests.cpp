#include "TestHarness.h"
#include "button.h"
#include "Arduino.h"

#define PIN 3

TEST_GROUP(ButtonTestGroup)
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

  
  Button* b;
  EventListnerSpy evSpy;
  
  void setup()
  {
    ArduinoStub.reset();
    b = new Button("test", PIN, 50);
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
  
  ArduinoStub.incTimeMs(51); //longer than debounce delay
  
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
  
  ArduinoStub.incTimeMs(51); //longer than debounce delay
  
  b->scan();
  LONGS_EQUAL(HIGH, b->getState());
  CHECK(evSpy.newData);
  CHECK(evSpy.serializedEvent.compare("test_1") == 0);
}

TEST(ButtonTestGroup, PressButtonShort)
{
  ArduinoStub.setDigitalRead(PIN, HIGH);

  b->scan();
  LONGS_EQUAL(LOW, b->getState());
  CHECK(!evSpy.newData);
    
  ArduinoStub.incTimeMs(49); //shorter than debounce delay
  
  b->scan();
  LONGS_EQUAL(LOW, b->getState());
  CHECK(!evSpy.newData);
}

TEST(ButtonTestGroup, ReleaseButton)
{
  ArduinoStub.setDigitalRead(PIN, HIGH);

  b->scan();

  ArduinoStub.incTimeMs(51); //longer than debounce delay

  b->scan();
  LONGS_EQUAL(HIGH, b->getState());

  ArduinoStub.setDigitalRead(PIN, LOW);

  b->scan();
  LONGS_EQUAL(HIGH, b->getState());
  
  ArduinoStub.incTimeMs(51); //longer than debounce delay

  b->scan();
  LONGS_EQUAL(LOW, b->getState());
}

