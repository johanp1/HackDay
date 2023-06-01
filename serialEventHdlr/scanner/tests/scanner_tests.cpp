#include <gtest/gtest.h>
#include "Arduino.h"
#include "scanner.h"
#include <iostream>
#include "src/axis_ctrl.h"

extern AxisCtrl horizontalAxisCtrl;

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


class ScannerTestFixture : public testing::Test 
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

TEST_F(ScannerTestFixture, InitTest)
{
   setup();
}

TEST_F(ScannerTestFixture, step1EventTest)
{
   String event_str{"step2_33\n"};
   Serial.setRecData(event_str);
   serialEvent();

   arduinoStub->IncTimeMs(1000);
}

TEST_F(ScannerTestFixture, horizontalMoveEventTest)
{
   String event_str{"hor_33\n"};
   Serial.setRecData(event_str);
   
   ASSERT_TRUE(horizontalAxisCtrl.GetPosition() == 0.0f);

   serialEvent();
   arduinoStub->IncTimeMs(1000);
   ASSERT_TRUE(horizontalAxisCtrl.GetPosition() == 33.0f);

   String event_str2{"hor_-40.0\n"};
   Serial.setRecData(event_str2);
   serialEvent();
   arduinoStub->IncTimeMs(1000);
   ASSERT_TRUE(horizontalAxisCtrl.GetPosition() == -7.0f);
}

}