#include <gtest/gtest.h>
#include "selector.h"
#include "Arduino.h"
#include <array>
#include <iostream>
#include <string>

constexpr int PIN = 2;

namespace {
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

class SelectorTestFixture : public testing::Test 
{
   protected: 
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
      ASSERT_TRUE(evSpy.newData);
      ASSERT_TRUE(evSpy.serializedEvent.compare(expected) == 0);
   }

   void SetUp()
   {
      arduinoStub->Reset();
      evSpy.reset();
      s = std::make_unique<Selector>("test", PIN, 100);
      s->addEventListner(&evSpy);
   }
   
   void TearDown()
   {
      evSpy.reset();
   }
};

TEST_F(SelectorTestFixture, Init)
{
  ASSERT_TRUE(0 == s->getState());
}

TEST_F(SelectorTestFixture, SteadyState)
{
  arduinoStub->SetAnalogPinVoltage(PIN, 0);

  s->scan();
  ASSERT_TRUE(0 == s->getState());
  
  arduinoStub->IncTime(101); //longer than debounce delay

  s->scan();
  ASSERT_TRUE(0 == s->getState());
  ASSERT_TRUE(!evSpy.newData);
}

TEST_F(SelectorTestFixture, checkNoTransitionShortTime)
{
	arduinoStub->SetAnalogPinVoltage(PIN, 1.7f);

	s->scan();
	ASSERT_TRUE(0 == s->getState());

	arduinoStub->IncTimeMs(99); //shorter than debounce delay

	s->scan();
	ASSERT_TRUE(0 == s->getState());
}

TEST_F(SelectorTestFixture, stateTransitions)
{
  string expected;
  
  gotoState(0);
  ASSERT_TRUE(0 == s->getState());
  ASSERT_TRUE(!evSpy.newData);  //no new event since 0 is the init state
  
  gotoState(1);
  ASSERT_TRUE(1 == s->getState());
  expected = "test_1";
  checkEvent(expected);

  gotoState(2);
  ASSERT_TRUE(2 == s->getState());
  expected = "test_2";
  checkEvent(expected);
  
  gotoState(3);
  ASSERT_TRUE(3 == s->getState());
  expected = "test_3";
  checkEvent(expected);
  
  gotoState(0);
  ASSERT_TRUE(0 == s->getState());
  expected = "test_0";
  checkEvent(expected);
}

TEST_F(SelectorTestFixture, stateTransitionsUserDefinedVals)
{
  std::unique_ptr<Selector> s_userDefined;
  unsigned int array[5] = {50u, 250u, 500u, 750u, 1000u};
  s_userDefined = std::make_unique<Selector>("test", PIN, 100, array, 5);
  s_userDefined->addEventListner(&evSpy);
  
  arduinoStub->SetAnalogPinVoltage(PIN, (5.0f*array[4])/1024); 
  s_userDefined->scan();
  arduinoStub->IncTimeMs(101); //longer than debounce delay
  s_userDefined->scan();
  ASSERT_TRUE(4 == s_userDefined->getState());

  arduinoStub->SetAnalogPinVoltage(PIN, (5.0f*array[3])/1024); 
  s_userDefined->scan();
  arduinoStub->IncTimeMs(101); //longer than debounce delay
  s_userDefined->scan();
  ASSERT_TRUE(3 == s_userDefined->getState());

  arduinoStub->SetAnalogPinVoltage(PIN, (5.0f*array[2])/1024); 
  s_userDefined->scan();
  arduinoStub->IncTimeMs(101); //longer than debounce delay
  s_userDefined->scan();
  ASSERT_TRUE(2 == s_userDefined->getState());

  arduinoStub->SetAnalogPinVoltage(PIN, (5.0f*array[1])/1024); 
  s_userDefined->scan();
  arduinoStub->IncTimeMs(101); //longer than debounce delay
  s_userDefined->scan();
  ASSERT_TRUE(1 == s_userDefined->getState());

  arduinoStub->SetAnalogPinVoltage(PIN, (5.0f*array[0])/1024); 
  s_userDefined->scan();
  arduinoStub->IncTimeMs(101); //longer than debounce delay
  s_userDefined->scan();
  ASSERT_TRUE(0 == s_userDefined->getState());
}

TEST_F(SelectorTestFixture, stateTransitionsUserThreshold)
{
  std::unique_ptr<Selector> s_userDefined;
  unsigned int array[5] = {50u, 250u, 500u, 750u, 1000u};
  s_userDefined = std::make_unique<Selector>("test", PIN, 100, array, 5, 10);
  s_userDefined->addEventListner(&evSpy);
  
  // set known state
  arduinoStub->SetAnalogPinVoltage(PIN, (5.0f*array[0])/1024); 
  s_userDefined->scan();
  arduinoStub->IncTimeMs(101); //longer than debounce delay
  s_userDefined->scan();
  ASSERT_TRUE(0 == s_userDefined->getState());

  // set slightly to small value for transition to state 1
  arduinoStub->SetAnalogPinVoltage(PIN, (5.0f*(array[1]-10))/1024); 
  s_userDefined->scan();
  arduinoStub->IncTimeMs(101); //longer than debounce delay
  s_userDefined->scan();
  ASSERT_TRUE(0 == s_userDefined->getState());

  // set ok value for state 1
  arduinoStub->SetAnalogPinVoltage(PIN, (5.0f*(array[1]-8))/1024); 
  s_userDefined->scan();
  arduinoStub->IncTimeMs(101); //longer than debounce delay
  s_userDefined->scan();
  ASSERT_TRUE(1 == s_userDefined->getState());

   // set slightly to big value for transition to state 2
  arduinoStub->SetAnalogPinVoltage(PIN, (5.0f*(array[2]+12))/1024); 
  s_userDefined->scan();
  arduinoStub->IncTimeMs(101); //longer than debounce delay
  s_userDefined->scan();
  ASSERT_TRUE(0 == s_userDefined->getState());

  // set ok value for state 1
  arduinoStub->SetAnalogPinVoltage(PIN, (5.0f*(array[2]+8))/1024); 
  s_userDefined->scan();
  arduinoStub->IncTimeMs(101); //longer than debounce delay
  s_userDefined->scan();
  ASSERT_TRUE(2 == s_userDefined->getState());
}

TEST_F(SelectorTestFixture, undefVolt)
{
  arduinoStub->SetAnalogPinVoltage(PIN, 2.83f);
  
  s->scan();
  arduinoStub->IncTimeMs(101); //longer than debounce delay
  s->scan();
  
  ASSERT_TRUE(0 == s->getState());
  ASSERT_TRUE(!evSpy.newData);
  
  arduinoStub->SetAnalogPinVoltage(PIN, 0.5f);
  
  s->scan();
  arduinoStub->IncTimeMs(101); //longer than debounce delay
  s->scan();
  
  ASSERT_TRUE(0 == s->getState());
  ASSERT_TRUE(!evSpy.newData);
}

} // namespace