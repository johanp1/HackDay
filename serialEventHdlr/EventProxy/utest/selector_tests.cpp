#include "TestHarness.h"
#include "selector.h"
#include "Arduino.h"
#include <array>
#include <iostream>
#include <string>

#define PIN 2

TEST_GROUP(SelectorTestGroup)
{
   class EventListnerSpy : public EventListner{
   public:
      void enventListnerSpy()
      {
         reset();
      };
      
      void HandleEvent(C_Event& e)
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
      float volt = 0.0f;
      array<unsigned int, 4> ad_val2state{250, 350, 500, 1024};

      try
      {
         volt = (5.0f*(float)ad_val2state.at(state))/1024; // reference voltage 5V, resolution 10 bits (1023 = 5V)
      }
      catch (const std::out_of_range& oor)
      {
         std::cerr << "Out of Range error: " << oor.what() << '\n';
      }
      
      arduinoStub->SetAnalogPinVoltage(PIN, volt);
      
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
      evSpy.reset();
   }
};

TEST(SelectorTestGroup, Init)
{
  LONGS_EQUAL(0, s->getState());
}

TEST(SelectorTestGroup, SteadyState)
{
  arduinoStub->SetAnalogPinVoltage(PIN, 0);

  s->scan();
  LONGS_EQUAL(0, s->getState());
  
  arduinoStub->IncTime(101); //longer than debounce delay

  s->scan();
  LONGS_EQUAL(0, s->getState());
  CHECK(!evSpy.newData);
}

TEST(SelectorTestGroup, checkNoTransitionShortTime)
{
	arduinoStub->SetAnalogPinVoltage(PIN, 1.7f);

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
  arduinoStub->SetAnalogPinVoltage(PIN, 2.83f);
  
  s->scan();
  arduinoStub->IncTimeMs(101); //longer than debounce delay
  s->scan();
  
  LONGS_EQUAL(0, s->getState());
  CHECK(!evSpy.newData);
  
  arduinoStub->SetAnalogPinVoltage(PIN, 0.5f);
  
  s->scan();
  arduinoStub->IncTimeMs(101); //longer than debounce delay
  s->scan();
  
  LONGS_EQUAL(0, s->getState());
  CHECK(!evSpy.newData);
}
