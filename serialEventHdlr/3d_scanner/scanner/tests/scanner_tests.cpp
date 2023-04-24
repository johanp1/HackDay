#include <gtest/gtest.h>
#include "Arduino.h"
#include "scanner.h"
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
   //ASSERT_TRUE(Serial.getData().compare("mpgPendant::setup()\n") == 0 );
}

TEST_F(ScannerTestFixture, step1EventTest)
{
   String event_str{"step2_33\n"};
   setup();
   Serial.setRecData(event_str);
   serialEvent();
}

}