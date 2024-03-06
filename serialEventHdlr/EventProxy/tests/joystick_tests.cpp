#include <gtest/gtest.h>
#include "joystick.h"
#include "Arduino.h"
//#include <array>
#include <iostream>
#include <string>

constexpr int PIN = 2;

inline float adValueToVolt(int adVal)
{
   return 5.0f*adVal/1023.0f;
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
      newData = true;
      last_event = e;
   };

   void reset()
   {
      newData = false;
   };
      
   void checkEvent(string& expected)
   {
      ASSERT_TRUE(newData);
      ASSERT_TRUE(last_event.serialize().s.compare(expected) == 0);
   }

   C_Event last_event;
   bool newData;
};

class JoystickTestFixture : public testing::Test 
{
   protected: 
   EventListnerSpy evSpy;
   std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();
   std::unique_ptr<Joystick> joystick;

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

   float AdVal2Volt(unsigned int val)
   {
      return (5.0f*val)/1024;
   }
};

TEST_F(JoystickTestFixture, Init)
{
   ASSERT_TRUE(0 == joystick->GetPos());
}

TEST_F(JoystickTestFixture, test_simple)
{
   string expected{"test_-100"}; 
   //arduinoStub->SetAnalogPinVoltage(PIN, 0);
   arduinoStub->SetAnalogPinVoltage(PIN, AdVal2Volt(0));
   joystick->scan();
   ASSERT_TRUE(-100 == joystick->GetPos());
   evSpy.checkEvent(expected);

   expected = "test_0";
   arduinoStub->SetAnalogPinVoltage(PIN, AdVal2Volt(512));
   joystick->scan();
   ASSERT_TRUE(0 == joystick->GetPos());
   evSpy.checkEvent(expected);

   expected = "test_100";
   arduinoStub->SetAnalogPinVoltage(PIN, AdVal2Volt(1023));
   joystick->scan();
   ASSERT_TRUE(100 == joystick->GetPos());
   evSpy.checkEvent(expected);
}

TEST_F(JoystickTestFixture, test_steady_state)
{
   // set neutral pos
   arduinoStub->SetAnalogPinVoltage(PIN, 2.505);
   joystick->scan();
   ASSERT_TRUE(0 == joystick->GetPos());

   evSpy.reset();
   joystick->scan();
   ASSERT_TRUE(0 == joystick->GetPos());
   ASSERT_TRUE(!evSpy.newData);

   // set new pos
   arduinoStub->SetAnalogPinVoltage(PIN, 2.1);
   joystick->scan();

   evSpy.reset();
   joystick->scan();
   ASSERT_TRUE(!evSpy.newData);
}

TEST_F(JoystickTestFixture, test_calibration_mid)
{
    arduinoStub->SetAnalogPinVoltage(PIN, AdVal2Volt(520));
    joystick->CalibrateMid();
    joystick->scan();
    ASSERT_TRUE(0 == joystick->GetPos());

    // check hi and low not changed by mid-calibration
    arduinoStub->SetAnalogPinVoltage(PIN, AdVal2Volt(1023));
    joystick->scan();
    ASSERT_TRUE(100 == joystick->GetPos());
    arduinoStub->SetAnalogPinVoltage(PIN, AdVal2Volt(0));
    joystick->scan();
    ASSERT_TRUE(-100 == joystick->GetPos());

    // calibrate again
    arduinoStub->SetAnalogPinVoltage(PIN, AdVal2Volt(500));
    joystick->CalibrateMid();
    joystick->scan();
    ASSERT_TRUE(0 == joystick->GetPos());

    // check hi and low not changed by mid-calibration
    arduinoStub->SetAnalogPinVoltage(PIN, AdVal2Volt(1023));
    joystick->scan();
    ASSERT_TRUE(100 == joystick->GetPos());
    arduinoStub->SetAnalogPinVoltage(PIN, AdVal2Volt(0));
    joystick->scan();
    ASSERT_TRUE(-100 == joystick->GetPos());
}

TEST_F(JoystickTestFixture, test_map_creation)
{
    // calibrate high value at ad_val = 1000
    arduinoStub->SetAnalogPinVoltage(PIN, AdVal2Volt(1000));
    joystick->CalibrateHi();
    joystick->scan();
    ASSERT_TRUE(100 == joystick->GetPos());

    // check mid and low not changed by hi-calibration
    arduinoStub->SetAnalogPinVoltage(PIN, AdVal2Volt(512));
    joystick->scan();
    ASSERT_TRUE(0 == joystick->GetPos());
    arduinoStub->SetAnalogPinVoltage(PIN, AdVal2Volt(0));
    joystick->scan();
    ASSERT_TRUE(-100 == joystick->GetPos());

    // calibrate low value at ad_val = 1000
    arduinoStub->SetAnalogPinVoltage(PIN, AdVal2Volt(100));
    joystick->CalibrateLow();
    joystick->scan();
    ASSERT_TRUE(-99 == joystick->GetPos()); // almost -100...

   // check mid and high not changed by low-calibration
    arduinoStub->SetAnalogPinVoltage(PIN, AdVal2Volt(1000));
    joystick->scan();
    ASSERT_TRUE(100 == joystick->GetPos());
    arduinoStub->SetAnalogPinVoltage(PIN, AdVal2Volt(512));
    joystick->scan();
    ASSERT_TRUE(0 == joystick->GetPos());
}


}