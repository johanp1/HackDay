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

enum Axis { kHorizontal, kVertical };
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

bool checkJogDone(Axis a, float expected_pos, bool debug = false)
{
   bool ret_val = false;
   float pos_according_to_axisctrl = 0.0f;
   string serial_data = Serial.getData();
   
   float pos_according_to_handler = stof(serial_data.substr(5, serial_data.length()));
   if (a == kHorizontal)
   {
      ret_val = substringFind(serial_data, "hpos"s);
      pos_according_to_axisctrl = horizontalAxisCtrl.GetPosition();
   }
   if (a == kVertical)
   {
      ret_val = substringFind(serial_data, "vpos"s);
      pos_according_to_axisctrl = verticalAxisCtrl.GetPosition();
   }

   if (debug)
   {
      cout << (a == kHorizontal ? "Horizontal:" : "Vertical:") << endl;
      cout << "serial_data " << serial_data << endl;
      cout << "expected_pos " << expected_pos << endl;
      cout << "pos_according_to_axisctrl " << pos_according_to_axisctrl << " " << checkPos(pos_according_to_axisctrl, expected_pos) << endl;
      cout << "pos_according_to_handler " << pos_according_to_handler << " " << checkPos(pos_according_to_handler, expected_pos) << endl;
   }
   
   return ret_val && checkPos(pos_according_to_handler, expected_pos) 
                  && checkPos(pos_according_to_axisctrl, expected_pos);
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

   Serial.clear();
   
   // Test Set Horizontal position ///////////////////////////////////////////////////
   serialSend(String{"hjog_33\n"});
   RunMs(3000);
   ASSERT_TRUE(checkJogDone(kHorizontal, 33.0f));

   serialSend(String{"hjog_-40\n"});
   RunMs(3000);
   ASSERT_TRUE(checkJogDone(kHorizontal, -7.0f));

   // Test Set Vertical position ////////////////////////////////////////////////////
   serialSend(String{"vjog_33\n"});
   RunMs(3000);
   ASSERT_TRUE(checkJogDone(kVertical, 33.0f));

   serialSend(String{"vjog_-40\n"});
   RunMs(3000);
   ASSERT_TRUE(checkJogDone(kVertical, -7.0f));

   // Test Set Horizontal start position ////////////////////////////////////////////
   // horizontal start is always 0
   ASSERT_TRUE(checkPos(horizontalAxisCtrl.GetPosition(), -7.0f, 0.25f));
   serialSend(String{"set_hs\n"});
   RunMs(500);
   ASSERT_TRUE(checkJogDone(kHorizontal, 0.0f));
   ASSERT_TRUE(checkPos(horizontalAxisCtrl.GetPosition(), 0.0f));

   // Test Set vertical start position ////////////////////////////////////////////
   // vertical start can be any angle
   ASSERT_TRUE(checkPos(verticalAxisCtrl.GetPosition(), -7.0f));
   serialSend(String{"set_vs\n"});
   RunMs(100);
   ASSERT_TRUE(checkPos(verticalAxisCtrl.GetPosition(), -7.0f));

   // Test Set vertical home position ////////////////////////////////////////////
   // vertical is always 0, transition to mode_1 = homed
   ASSERT_TRUE(checkPos(verticalAxisCtrl.GetPosition(), -7.0f));
   serialSend(String{"set_vh\n"});
   RunMs(100);
   {
      auto serial_data = Serial.getData();
      ASSERT_TRUE(substringFind(serial_data, "mode_1"s));
      ASSERT_TRUE(substringFind(serial_data, "vpos_0"s));

      ASSERT_TRUE(checkPos(verticalAxisCtrl.GetPosition(), 0.0f));
   }
   
   /* also test:
   mode
   hups
   vups
   rf
   hi
   vi
   */
   //ASSERT_TRUE(checkJogDone(kVertical, 0.0f));

   // Test Set Horizontal end position /////////////////////////////////////////////
   /*serialSend(String{"hjog_29.7.0\n"});
   RunMs(2000);
   serialSend(String{"set_he\n"});
   RunMs(10);

   serialSend(String{"hjog_-29.7\n"}); // go back to abs pos 0
   RunMs(2000);*/

   // Test start test mode /////////////////////////////////////////////////////////
//   serialSend(String{"mode_1\n"});
//   RunMs(9000);
//   ASSERT_TRUE(checkPos(horizontalAxisCtrl.GetPosition(), 0.0, 0.1));
}

}