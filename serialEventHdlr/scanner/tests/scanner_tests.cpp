#include <gtest/gtest.h>
#include "Arduino.h"
#include "scanner.h"
#include <iostream>
#include "src/axis_ctrl.h"
#include "src/scanner_ctrl.h"
#include "LIDARLite.h"

extern AxisCtrl horizontalAxisCtrl;
extern AxisCtrl verticalAxisCtrl;
extern LIDARLite lidar;
extern ScannerCtrl<LIDARLite> scannerCtrl;
extern void TIMER2_COMPA_vect();

namespace {

std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();

// find str2 in str1
bool substringFind(const std::string& str1, const std::string& str2)
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
   return substringFind(Serial.getData(), str);
}

void serialSend(const String& s)
{
   String temp_string = String(s);

   Serial.setRecData(temp_string);
   serialEvent();
}

void RunMs(unsigned int ms)
{
   for (int i = 0; i < ms; i++)
   {
      TIMER2_COMPA_vect();

      if (i%5 == 0)
      {
         loop();
      }

      arduinoStub->IncTimeMs(1);
   }
}

bool checkPos(float actual, float expected, float tol = 0.1f)
{
   //cout << "actual pos: " << actual << ", expected pos: " << expected << endl;
   return (actual <= expected + tol) && (actual >= expected - tol);
}

TEST(ScannerTestSuite, scannerTest)
{
   setup();
   
   ASSERT_TRUE(arduinoStub->GetMode(2) == OUTPUT); // motor1_dir_pin
   ASSERT_TRUE(arduinoStub->GetMode(3) == OUTPUT); // motor2_dir_pin
   ASSERT_TRUE(arduinoStub->GetMode(5) == OUTPUT); // motor1_step_pin
   ASSERT_TRUE(arduinoStub->GetMode(6) == OUTPUT); // motor2_step_pin
   ASSERT_TRUE(arduinoStub->GetMode(8) == OUTPUT); // enable_pin

   ASSERT_TRUE(horizontalAxisCtrl.GetPosition() == 0.0f);
   ASSERT_TRUE(verticalAxisCtrl.GetPosition() == 0.0f);

   // Test Set Horizontal position ///////////////////////////////////////////////////
   serialSend(String{"hrm_33\n"});
   RunMs(2000);
  
   ASSERT_TRUE(checkPos(horizontalAxisCtrl.GetPosition(), 33.0f, 0.25f));

   serialSend(String{"hrm_-40\n"});
   RunMs(2000);
   ASSERT_TRUE(checkPos(horizontalAxisCtrl.GetPosition(), -7.0f, 0.25f));

   // Test Set Vertical position ////////////////////////////////////////////////////
   serialSend(String{"vrm_33\n"});
   RunMs(2000);
   ASSERT_TRUE(checkPos(verticalAxisCtrl.GetPosition(), 33.0f, 0.25f));

   serialSend(String{"vrm_-40\n"});
   RunMs(2000);
   ASSERT_TRUE(checkPos(verticalAxisCtrl.GetPosition(), -7.0f, 0.25f));

   // Test Set Horizontal start position ////////////////////////////////////////////
   ASSERT_TRUE(checkPos(horizontalAxisCtrl.GetPosition(), -7.0f, 0.25f));
   serialSend(String{"set_hs\n"});
   RunMs(10);
   ASSERT_TRUE(checkPos(horizontalAxisCtrl.GetPosition(), 0.0f));

   // Test Set Horizontal end position /////////////////////////////////////////////
   serialSend(String{"hrm_29.7.0\n"});
   RunMs(2000);
   serialSend(String{"set_he\n"});
   RunMs(10);

   serialSend(String{"hrm_-29.7\n"}); // go back to abs pos 0
   RunMs(2000);

   // Test start test mode /////////////////////////////////////////////////////////
//   serialSend(String{"mode_1\n"});
//   RunMs(9000);
//   ASSERT_TRUE(checkPos(horizontalAxisCtrl.GetPosition(), 0.0, 0.1));
}

}