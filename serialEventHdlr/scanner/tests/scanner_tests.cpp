#include <gtest/gtest.h>
#include "Arduino.h"
#include "scanner.h"
#include <iostream>
#include "src/axis_ctrl.h"

extern AxisCtrl horizontalAxisCtrl;
extern AxisCtrl verticalAxisCtrl;
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
      arduinoStub->IncTimeMs(1);
      TIMER2_COMPA_vect();
   }
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

   serialSend(String{"hor_33\n"});
   RunMs(1000);
   ASSERT_TRUE(horizontalAxisCtrl.GetPosition() == 33.0f);

   serialSend(String{"hor_-40\n"});
   RunMs(1000);
   ASSERT_TRUE(horizontalAxisCtrl.GetPosition() == -7.0f);

   serialSend(String{"ver_33\n"});
   RunMs(1000);
   ASSERT_TRUE(verticalAxisCtrl.GetPosition() == 33.0f);

   serialSend(String{"ver_-40\n"});
   RunMs(1000);
   ASSERT_TRUE(verticalAxisCtrl.GetPosition() == -7.0f);
}

}