#include <gtest/gtest.h>
#include "joystick.h"
#include "Arduino.h"
//#include <array>
#include <iostream>
#include <string>


constexpr int PIN = 2;

inline float adValueToVolt(int adVal)
{
   return 5.0f*(float)adVal/1023.0f;
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
      arduinoStub->SetAnalogPinAdVal(PIN, 512);

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
      return (5.0f*val)/1024.0f;
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
   arduinoStub->SetAnalogPinAdVal(PIN, 0);
   joystick->scan();
   ASSERT_EQ(-100, joystick->GetPos());
   evSpy.checkEvent(expected);

   expected = "test_0";
   arduinoStub->SetAnalogPinAdVal(PIN, 512);
   joystick->scan();
   ASSERT_EQ(0, joystick->GetPos());
   evSpy.checkEvent(expected);

   expected = "test_100";
   arduinoStub->SetAnalogPinAdVal(PIN, 1023);
   joystick->scan();
   ASSERT_EQ(100, joystick->GetPos());
   evSpy.checkEvent(expected);
}

TEST_F(JoystickTestFixture, test_steady_state)
{
   // set neutral pos
   arduinoStub->SetAnalogPinVoltage(PIN, 2.505);
   joystick->scan();
   ASSERT_EQ(0, joystick->GetPos());

   evSpy.reset();
   joystick->scan();
   ASSERT_EQ(0, joystick->GetPos());
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
    arduinoStub->SetAnalogPinAdVal(PIN, 520);
    joystick->Calibrate(mid);
    joystick->scan();
    ASSERT_EQ(0, joystick->GetPos());

    // check hi and low not changed by mid-calibration
    arduinoStub->SetAnalogPinAdVal(PIN, 1023);
    joystick->scan();
    ASSERT_EQ(100, joystick->GetPos());
    arduinoStub->SetAnalogPinAdVal(PIN, 0);
    joystick->scan();
    ASSERT_EQ(-100, joystick->GetPos());

    // calibrate again
    arduinoStub->SetAnalogPinAdVal(PIN, 500);
    joystick->Calibrate(mid);
    joystick->scan();
    ASSERT_EQ(0, joystick->GetPos());

    // check hi and low not changed by mid-calibration
    arduinoStub->SetAnalogPinAdVal(PIN, 1023);
    joystick->scan();
    ASSERT_EQ(99, joystick->GetPos()); // close enough
    arduinoStub->SetAnalogPinAdVal(PIN, 0);
    joystick->scan();
    ASSERT_EQ(-100, joystick->GetPos());
}

TEST_F(JoystickTestFixture, test_map_creation)
{
    int eeprom_readback;

    // calibrate high
    arduinoStub->SetAnalogPinAdVal(PIN, 1000);
    joystick->Calibrate(hi);
    joystick->scan();
    ASSERT_EQ(100, joystick->GetPos());
    //EEPROM.get(sizeof(int), eeprom_readback);
    //ASSERT_EQ(eeprom_readback, 1000); // close enough

    // check mid and low not changed by hi-calibration
    arduinoStub->SetAnalogPinAdVal(PIN, 512);
    joystick->scan();
    ASSERT_EQ(0, joystick->GetPos());
    arduinoStub->SetAnalogPinAdVal(PIN, 0);
    joystick->scan();
    ASSERT_EQ(-100, joystick->GetPos());

    // calibrate low value at ad_val = 1000
    arduinoStub->SetAnalogPinAdVal(PIN, 100);
    joystick->Calibrate(low);
    joystick->scan();
    ASSERT_EQ(-100, joystick->GetPos()); // almost -100...
    //EEPROM.get(0, eeprom_readback);
    //ASSERT_EQ(eeprom_readback, 100); // close enough

   // check mid and high not changed by low-calibration
    arduinoStub->SetAnalogPinAdVal(PIN, 1000);
    joystick->scan();
    ASSERT_EQ(100, joystick->GetPos());
    arduinoStub->SetAnalogPinAdVal(PIN, 512);
    joystick->scan();
    ASSERT_EQ(0, joystick->GetPos());

   ASSERT_EQ(100, joystick->GetLimits().x_low);
   ASSERT_EQ(512, joystick->GetLimits().x_mid);
   ASSERT_EQ(1000, joystick->GetLimits().x_hi);
}

TEST_F(JoystickTestFixture, test_calibrated)
{
   auto constexpr my_pin = 1;

   arduinoStub->SetAnalogPinAdVal(my_pin, 600); // initial value of ad converter
   Joystick my_joystick("apa", my_pin, false, 100, 600, 900);
   ASSERT_EQ(0, my_joystick.GetPos());

   my_joystick.scan();
   ASSERT_EQ(0, my_joystick.GetPos());

   arduinoStub->SetAnalogPinAdVal(my_pin, 100);
   my_joystick.scan();
   ASSERT_EQ(-99, my_joystick.GetPos());

   arduinoStub->SetAnalogPinAdVal(my_pin, 900);
   my_joystick.scan();
   ASSERT_EQ(100, my_joystick.GetPos());
}

TEST_F(JoystickTestFixture, test_flipped)
{
   auto constexpr my_pin = 1;

   arduinoStub->SetAnalogPinAdVal(my_pin, 512); // initial value of ad converter
   Joystick my_joystick("apa", my_pin, true);
   
   my_joystick.scan();
   ASSERT_EQ(0, my_joystick.GetPos());

   arduinoStub->SetAnalogPinAdVal(my_pin, 1023);
   my_joystick.scan();
   ASSERT_EQ(-100, my_joystick.GetPos());

   arduinoStub->SetAnalogPinAdVal(my_pin, 0);
   my_joystick.scan();
   ASSERT_EQ(100, my_joystick.GetPos());
}

TEST_F(JoystickTestFixture, test_flipped_calibrated)
{
   auto constexpr my_pin = 1;

   arduinoStub->SetAnalogPinAdVal(my_pin, 600); // initial value of ad converter
   Joystick my_joystick("apa", my_pin, true, 100, 600, 900);
   ASSERT_EQ(0, my_joystick.GetPos());

   my_joystick.scan();
   ASSERT_EQ(0, my_joystick.GetPos());

   arduinoStub->SetAnalogPinAdVal(my_pin, 100);
   my_joystick.scan();
   ASSERT_EQ(100, my_joystick.GetPos());

   arduinoStub->SetAnalogPinAdVal(my_pin, 900);
   my_joystick.scan();
   ASSERT_EQ(-100, my_joystick.GetPos());
}

}