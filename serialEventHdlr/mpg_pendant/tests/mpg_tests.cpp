#include <gtest/gtest.h>
#include "Arduino.h"
#include "mpg_pendant.h"

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

TEST_F(MpgTestFixture, PressRunButtonTest)
{
   setup();

   // press button
   arduinoStub->SetDigitalRead(kRunButtonPin, HIGH);
   loop();
   ASSERT_FALSE(hasBeenSent("run_1\n"));
   arduinoStub->IncTimeMs(kButtonDebounceDelay + 1);
   loop();
   ASSERT_TRUE(hasBeenSent("run_1\n"));

   // release button
   arduinoStub->SetDigitalRead(kRunButtonPin, LOW);
   loop();
   ASSERT_FALSE(hasBeenSent("run_0\n"));
   arduinoStub->IncTimeMs(kButtonDebounceDelay + 1);
   loop();
   ASSERT_TRUE(hasBeenSent("run_0\n"));
}

TEST_F(MpgTestFixture, CWJogTest)
{
   setup();

   // CW rotate jog wheel
   arduinoStub->SetDigitalRead(kEncoderDirectionPin, HIGH);
   arduinoStub->InvokeInterrupt(HIGH); // puts event in buffer
   ASSERT_FALSE(hasBeenSent("jog_1\n"));
   loop();                             // pop buffer, send event   
   ASSERT_TRUE(hasBeenSent("jog_1\n"));

   // CCW rotate jog wheel
   arduinoStub->SetDigitalRead(kEncoderDirectionPin, LOW);
   arduinoStub->InvokeInterrupt(HIGH); // puts event in buffer
   ASSERT_FALSE(hasBeenSent("jog_0\n"));
   loop();                             // pop buffer, send event   
   ASSERT_TRUE(hasBeenSent("jog_0\n"));
}

}