#include <gtest/gtest.h>
#include "Arduino.h"
#include <EEPROM.h>
#include "mpg_pendant_lathe_mk2.h"
#include <iostream>

namespace {

// find str2 in str1
bool SubstringFind(const std::string& str1, const std::string& str2)
{
   auto retVal = false;
   
   if (str1.find(str2) != string::npos)
   {
      retVal = true; //.. found.
   } 
   return retVal;
}

bool hasBeenSent(const std::string& str)
{
   return SubstringFind(Serial.getData(), str);
}

void serialSend(const String& s)
{
   String temp_string = String(s);

   Serial.setRecData(temp_string);
   serialEvent();
}

class MpgTestFixture : public testing::Test 
{  
   protected: 
   std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();

   void SetUp() override
   {
      arduinoStub->Reset();
      Serial.clear();
      EEPROM.clear();

      arduinoStub->SetDigitalRead(kJogPosButtonPin, HIGH);
   }
   
   void TearDown()
   {
   }
};

TEST_F(MpgTestFixture, InitTest)
{ 
   setup();
   ASSERT_TRUE(Serial.getData().compare("mpgPendant::setup()\n") == 0 );
}

// test that heart-beat is sent after "kHeartbeatPeriod" ms has passed
TEST_F(MpgTestFixture, heartbeatTest)
{
   // precondition
   loop();
   Serial.clear();  // remove som initial noise

   arduinoStub->IncTimeMs(kHeartbeatPeriod/2);
   loop();
   ASSERT_FALSE(hasBeenSent("hb_1"));

   arduinoStub->IncTimeMs(kHeartbeatPeriod/2 + 1);
   loop();
   ASSERT_TRUE(hasBeenSent("hb_1"));
}

TEST_F(MpgTestFixture, PressPlusButtonTest)
{
   // press button
   arduinoStub->SetDigitalRead(kJogPosButtonPin, LOW);
   loop();
   ASSERT_FALSE(hasBeenSent("jpos_1\n"));
   arduinoStub->IncTimeMs(kButtonDebounceDelay + 1);
   loop();
   ASSERT_TRUE(hasBeenSent("jpos_1\n"));

   // release button
   arduinoStub->SetDigitalRead(kJogPosButtonPin, HIGH);
   loop();
   ASSERT_FALSE(hasBeenSent("jpos_0\n"));
   arduinoStub->IncTimeMs(kButtonDebounceDelay + 1);
   loop();
   ASSERT_TRUE(hasBeenSent("jpos_0\n"));
}

TEST_F(MpgTestFixture, selectAxisTest)
{
   arduinoStub->SetAnalogPinVoltage(kAxisSelectorPin, 1.3);
   loop();
   arduinoStub->IncTimeMs(kSelectorDebounceDelay + 1);
   loop();
   ASSERT_TRUE(hasBeenSent("sela_1\n"));
}

TEST_F(MpgTestFixture, calibrateJoysticksTest)
{
   CalibData ee_readback;
   arduinoStub->SetAnalogPinAdVal(kJoystickXPin, 510);
   arduinoStub->SetAnalogPinAdVal(kJoystickZPin, 511);
   serialSend(String{"calx_mid\n"});
   serialSend(String{"calz_mid\n"});

   arduinoStub->SetAnalogPinAdVal(kJoystickXPin, 1021);
   arduinoStub->SetAnalogPinAdVal(kJoystickZPin, 1022);
   serialSend(String{"calx_hi\n"});
   serialSend(String{"calz_hi\n"});

   arduinoStub->SetAnalogPinAdVal(kJoystickXPin, 1);
   arduinoStub->SetAnalogPinAdVal(kJoystickZPin, 2);
   serialSend(String{"calx_low\n"});
   serialSend(String{"calz_low\n"});

   EEPROM.get(0, ee_readback);
   ASSERT_EQ(ee_readback.x.limits.hi, 1021);
   ASSERT_EQ(ee_readback.z.limits.hi, 1022);
   //ASSERT_EQ(ee_readback.x.limits.x_mid, 510);
   //ASSERT_EQ(ee_readback.z.limits.x_mid, 511);
   ASSERT_EQ(ee_readback.x.limits.low, 1);
   ASSERT_EQ(ee_readback.z.limits.low, 2);
}

TEST_F(MpgTestFixture, moveJoystickXTest)
{
   // joystick in middle pos (0)
   //arduinoStub->SetAnalogPinVoltage(kJoystickZPin, 3.5);
   loop();
   // nothing should have happened
   ASSERT_TRUE(SubstringFind(Serial.getData(), ""));

   arduinoStub->SetAnalogPinVoltage(kJoystickXPin, 2.0);
   loop();
   ASSERT_TRUE(hasBeenSent("x_"));
}

TEST_F(MpgTestFixture, moveJoystickZTest)
{
   // joystick in middle pos (0)
   //arduinoStub->SetAnalogPinVoltage(kJoystickZPin, 2.5);
   //loop();
   // nothing should have happened
   //ASSERT_TRUE(SubstringFind(Serial.getData(), ""));

   //move the joystick
   arduinoStub->SetAnalogPinVoltage(kJoystickZPin, 3.6);
   loop();
   // check for joystick event
   ASSERT_TRUE(hasBeenSent("z_"));
}

TEST_F(MpgTestFixture, flipJoystickTest)
{
   CalibData eeprom_readback;

   serialSend(String{"flipx_1\n"});
   
   EEPROM.get(0, eeprom_readback);
   ASSERT_EQ(eeprom_readback.x.flipped, true);
}

}