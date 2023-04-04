#include <gtest/gtest.h>
#include "Arduino.h"
#include "mpg_pendant_lathe.h"
#include <iostream>
#include <LiquidCrystal_PCF8574.h>
#include "model.h"

extern LiquidCrystal_PCF8574 lcd;
extern Model lcdModel;

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

bool onLcd(const std::string& str, uint8_t row)
{
   return SubstringFind(lcd.getRow(row).s, str);
}

class MpgTestFixture : public testing::Test 
{  
   protected: 
   std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();

   void SetUp() override
   {
      arduinoStub->Reset();
      Serial.clear();
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
   setup();
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
   setup();

   // press button
   arduinoStub->SetDigitalRead(kJogPosButtonPin, HIGH);
   loop();
   ASSERT_FALSE(hasBeenSent("jpos_1\n"));
   arduinoStub->IncTimeMs(kButtonDebounceDelay + 1);
   loop();
   ASSERT_TRUE(hasBeenSent("jpos_1\n"));

   // release button
   arduinoStub->SetDigitalRead(kJogPosButtonPin, LOW);
   loop();
   loop();
   loop();
   ASSERT_FALSE(hasBeenSent("jpos_0\n"));
   //arduinoStub->IncTimeMs(kButtonDebounceDelay + 1);
   loop();
   loop();
   loop();
   ASSERT_TRUE(hasBeenSent("jpos_0\n"));
}

TEST_F(MpgTestFixture, spindleSpeedEventTest)
{
   String spindle_speed_event_serialized{"ss_100\n"};
   setup();
   Serial.setRecData(spindle_speed_event_serialized);
   serialEvent();
  
   ASSERT_TRUE(lcdModel.GetSpindleSpeed() == 100);
}

TEST_F(MpgTestFixture, xPosEventTest)
{
   String event_str{"xpos_1.1\n"};
   setup();
   Serial.setRecData(event_str);
   serialEvent();
   ASSERT_NEAR(lcdModel.GetX(), 1.1f, 0.1f);
}

TEST_F(MpgTestFixture, zPosEventTest)
{
   String event_str{"zpos_33.3\n"};
   setup();
   Serial.setRecData(event_str);
   serialEvent();
   ASSERT_NEAR(lcdModel.GetZ(), 33.3f, 0.1f);
}

TEST_F(MpgTestFixture, selectSpindleViewTest)
{
   setup();
   arduinoStub->SetAnalogPinVoltage(kAxisSelectorPin, 2.6);
   loop();
   arduinoStub->IncTimeMs(kSelectorDebounceDelay + 1);
   loop();
   ASSERT_TRUE(hasBeenSent("sela_2\n"));
   ASSERT_TRUE(onLcd("spindle speed:", 0));
}

TEST_F(MpgTestFixture, selectAxisViewTest)
{
   setup();
   arduinoStub->SetAnalogPinVoltage(kAxisSelectorPin, 1.3);
   loop();
   arduinoStub->IncTimeMs(kSelectorDebounceDelay + 1);
   loop();
   ASSERT_TRUE(hasBeenSent("sela_1\n"));
   ASSERT_TRUE(onLcd(" x:", 0));
   ASSERT_TRUE(onLcd("*z:", 1));
}

}