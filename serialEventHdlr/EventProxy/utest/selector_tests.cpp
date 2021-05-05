#include "TestHarness.h"
#include "selector.h"
#include "Arduino.h"

#define PIN 2

TEST_GROUP(SelectorTestGroup)
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

  
   ;
   EventListnerSpy evSpy;
   std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();
   std::unique_ptr<Selector> s;

   void gotoState(byte state)
   {
      //byte oldState = s->getState();
      unsigned const int volt2state[4] = { 250, 350, 500, 1030 };
      unsigned int volt = volt2state[state];
      
      arduinoStub->SetAnalogRead(PIN, (int)volt);
      
      s->scan();
      arduinoStub->IncTimeMs(101); //longer than debounce delay
      s->scan();
   }
   
   void checkEvent(string& expected)
   {
      CHECK(evSpy.newData);
      CHECK(evSpy.serializedEvent.compare(expected) == 0);
   }

   void setup()
   {
      arduinoStub->Reset();
      evSpy.reset();
      s = std::make_unique<Selector>("test", PIN, 100);
      s->addEventListner(&evSpy);
   }
   
   void teardown()
   {
      s.reset();
   }

};

TEST(SelectorTestGroup, Init)
{
  LONGS_EQUAL(0, s->getState());
}

TEST(SelectorTestGroup, SteadyState)
{
  arduinoStub->SetAnalogRead(PIN, 0);

  s->scan();
  LONGS_EQUAL(0, s->getState());
  
  arduinoStub->IncTime(101); //longer than debounce delay

  s->scan();
  LONGS_EQUAL(0, s->getState());
  CHECK(!evSpy.newData);
}

TEST(SelectorTestGroup, checkNoTransitionShortTime)
{
	arduinoStub->SetAnalogRead(PIN, 340);

	s->scan();
	LONGS_EQUAL(0, s->getState());

	arduinoStub->IncTimeMs(99); //shorter than debounce delay

	s->scan();
	LONGS_EQUAL(0, s->getState());
}

TEST(SelectorTestGroup, stateTransitions)
{
  string expected;
  
  gotoState(0);
  LONGS_EQUAL(0, s->getState());
  CHECK(!evSpy.newData);  //no new event since 0 is the init state
  
  gotoState(1);
  LONGS_EQUAL(1, s->getState());
  expected = "test_1";
  checkEvent(expected);

  gotoState(2);
  LONGS_EQUAL(2, s->getState());
  expected = "test_2";
  checkEvent(expected);
  
  gotoState(3);
  LONGS_EQUAL(3, s->getState());
  expected = "test_3";
  checkEvent(expected);
  
  gotoState(0);
  LONGS_EQUAL(0, s->getState());
  expected = "test_0";
  checkEvent(expected);
}

TEST(SelectorTestGroup, undefVolt)
{
  arduinoStub->SetAnalogRead(PIN, 1100);
  
  s->scan();
  arduinoStub->IncTimeMs(101); //longer than debounce delay
  s->scan();
  
  LONGS_EQUAL(0, s->getState());
  CHECK(!evSpy.newData);
  
  arduinoStub->SetAnalogRead(PIN, 580);
  
  s->scan();
  arduinoStub->IncTimeMs(101); //longer than debounce delay
  s->scan();
  
  LONGS_EQUAL(0, s->getState());
  CHECK(!evSpy.newData);
  
  arduinoStub->SetAnalogRead(PIN, 100);
  
  s->scan();
  arduinoStub->IncTimeMs(101); //longer than debounce delay
  s->scan();
  
  LONGS_EQUAL(0, s->getState());
  CHECK(!evSpy.newData);
}
