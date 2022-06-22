#include <gtest/gtest.h>
#include "selector2.h"
#include "Arduino.h"
#include <array>
#include <iostream>
#include <string>

constexpr int PIN1 = 2;
constexpr int PIN2 = 3;
constexpr int PIN3 = 4;


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

class Selector2TestFixture : public testing::Test 
{
   protected: 
   EventListnerSpy evSpy;
   std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();
   std::unique_ptr<Selector2> s;

   void checkEvent(string& expected)
   {
      ASSERT_TRUE(evSpy.newData);
      ASSERT_TRUE(evSpy.serializedEvent.compare(expected) == 0);
   }

   void SetUp()
   {
      arduinoStub->Reset();
      evSpy.reset();
      s = std::make_unique<Selector2>("test", PIN1, PIN2, PIN3, 100);
      s->addEventListner(&evSpy);
   }
   
   void TearDown()
   {
   }
};

TEST_F(Selector2TestFixture, Init)
{
  ASSERT_TRUE(true);
}

TEST_F(Selector2TestFixture, SteadyState)
{
  arduinoStub->SetDigitalRead(PIN1, HIGH);
  arduinoStub->SetDigitalRead(PIN2, HIGH);
  arduinoStub->SetDigitalRead(PIN3, HIGH);

  s->scan();  
  arduinoStub->IncTime(101); //longer than debounce delay
  s->scan();
  ASSERT_TRUE(!evSpy.newData);
}

TEST_F(Selector2TestFixture, checkNoTransitionShortTime)
{
   arduinoStub->SetDigitalRead(PIN1, HIGH);
   arduinoStub->SetDigitalRead(PIN2, HIGH);
   arduinoStub->SetDigitalRead(PIN3, HIGH);

	s->scan();
	arduinoStub->IncTimeMs(99); //shorter than debounce delay
	s->scan();
	ASSERT_TRUE(!evSpy.newData);
}

TEST_F(Selector2TestFixture, checkTransitionAfterTimeout)
{
   arduinoStub->SetDigitalRead(PIN1, HIGH);
   arduinoStub->SetDigitalRead(PIN2, HIGH);
   arduinoStub->SetDigitalRead(PIN3, LOW);

	s->scan();
	arduinoStub->IncTimeMs(101); //shorter than debounce delay
	s->scan();
	ASSERT_TRUE(evSpy.newData);
   ASSERT_TRUE(evSpy.serializedEvent.compare("test_3") == 0);
}

TEST_F(Selector2TestFixture, checkTransitionState1)
{
   arduinoStub->SetDigitalRead(PIN1, LOW);
   arduinoStub->SetDigitalRead(PIN2, HIGH);
   arduinoStub->SetDigitalRead(PIN3, HIGH);

	s->scan();
	arduinoStub->IncTimeMs(101); //shorter than debounce delay
	s->scan();
	ASSERT_TRUE(evSpy.newData);
   ASSERT_TRUE(evSpy.serializedEvent.compare("test_1") == 0);
}

TEST_F(Selector2TestFixture, checkTransitionState2)
{
   arduinoStub->SetDigitalRead(PIN1, HIGH);
   arduinoStub->SetDigitalRead(PIN2, LOW);
   arduinoStub->SetDigitalRead(PIN3, HIGH);

	s->scan();
	arduinoStub->IncTimeMs(101); //shorter than debounce delay
	s->scan();
	ASSERT_TRUE(evSpy.newData);
   ASSERT_TRUE(evSpy.serializedEvent.compare("test_2") == 0);
}

} // namespace