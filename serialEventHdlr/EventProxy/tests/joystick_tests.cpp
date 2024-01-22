#include <gtest/gtest.h>
#include "joystick.h"
#include "Arduino.h"
//#include <array>
#include <iostream>
#include <string>

constexpr int PIN = 2;

inline float adValueToVolt(int adVal)
{
   return (float)(5.0f*adVal/1024);
};

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

class JoystickTestFixture : public testing::Test 
{
   protected: 
   EventListnerSpy evSpy;
   std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();
   std::unique_ptr<Joystick> joystick;
   
   void checkEvent(string& expected)
   {
      ASSERT_TRUE(evSpy.newData);
      ASSERT_TRUE(evSpy.serializedEvent.compare(expected) == 0);
   }

   void SetUp()
   {
      arduinoStub->Reset();
      evSpy.reset();
      joystick = std::make_unique<Joystick>("test", PIN);
      joystick->addEventListner(&evSpy);
   }
   
   void TearDown()
   {
      evSpy.reset();
   }
};

TEST_F(JoystickTestFixture, Init)
{
   ASSERT_TRUE(0 == joystick->GetPos());
}

TEST_F(JoystickTestFixture, SteadyState)
{
   // precondition, got to known state (0)
   arduinoStub->SetAnalogPinVoltage(PIN, 0);
   joystick->scan();
   std::cout<<joystick->GetPos()<<std::endl;
   ASSERT_TRUE(-102 == joystick->GetPos());

   arduinoStub->SetAnalogPinVoltage(PIN, 2.505);
   joystick->scan();
   std::cout<<joystick->GetPos()<<std::endl;
   ASSERT_TRUE(0 == joystick->GetPos());

   arduinoStub->SetAnalogPinVoltage(PIN, 5);
   joystick->scan();
   std::cout<<joystick->GetPos()<<std::endl;
   ASSERT_TRUE(101 == joystick->GetPos());

   //ASSERT_TRUE(!evSpy.newData);
}

}