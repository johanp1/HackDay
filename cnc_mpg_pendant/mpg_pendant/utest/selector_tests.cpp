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
  
  void gotoState(byte state)
  {
    //byte oldState = s->getState();
	  unsigned const int volt2state[4] = { 250, 350, 500, 1030 };
	  unsigned int volt = volt2state[state];

	  ArduinoStub.setAnalogRead(PIN, (int)volt);

	  s->scan();
	  ArduinoStub.incTime(101); //longer than debounce delay
	  s->scan();
  }
  
  void checkEvent(unsigned int evData, string& evSource)
  {
	  CHECK(evSpy.newData);
	  LONGS_EQUAL(evData, evSpy.eventData);
	  CHECK(evSpy.eventSource.compare(evSource) == 0);
  }

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
  CHECK(!evSpy.newData);
}

TEST(SelectorTestGroup, checkNoTransitionShortTime)
{
	ArduinoStub.setAnalogRead(PIN, 340);

	s->scan();
	LONGS_EQUAL(0, s->getState());

	ArduinoStub.incTime(99); //shorter than debounce delay

	s->scan();
	LONGS_EQUAL(0, s->getState());
}

TEST(SelectorTestGroup, stateTransitions)
{
  string str = string("test");
  
  gotoState(0);
  LONGS_EQUAL(0, s->getState());
  CHECK(!evSpy.newData);  //no new event since 0 is the init state
  
  gotoState(1);
  LONGS_EQUAL(1, s->getState());
  checkEvent(1, str);

  gotoState(2);
  LONGS_EQUAL(2, s->getState());
  checkEvent(2, str);
  
  gotoState(3);
  LONGS_EQUAL(3, s->getState());
  checkEvent(3, str);
  
  gotoState(0);
  LONGS_EQUAL(0, s->getState());
  checkEvent(0, str);
}

TEST(SelectorTestGroup, undefVolt)
{
	ArduinoStub.setAnalogRead(PIN, 1000);

	s->scan();
	ArduinoStub.incTime(101); //longer than debounce delay
	s->scan();

	LONGS_EQUAL(0, s->getState());
	CHECK(!evSpy.newData);

	ArduinoStub.setAnalogRead(PIN, 535);

	s->scan();
	ArduinoStub.incTime(101); //longer than debounce delay
	s->scan();

	LONGS_EQUAL(0, s->getState());
	CHECK(!evSpy.newData);

	ArduinoStub.setAnalogRead(PIN, 100);

	s->scan();
	ArduinoStub.incTime(101); //longer than debounce delay
	s->scan();

	LONGS_EQUAL(0, s->getState());
	CHECK(!evSpy.newData);
}
