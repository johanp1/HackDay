#include <gtest/gtest.h>
#include "extruder.h"
#include "Arduino.h"
#include <iostream>

constexpr int c_tempPin = 1;
constexpr int c_pwmPin = 2;
std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();

namespace {
TEST(ExtruderTestGroup, init)
{
   Extruder extruder(c_tempPin, c_pwmPin);
   ASSERT_EQ(INPUT, arduinoStub->GetMode(c_tempPin));
   ASSERT_EQ(OUTPUT, arduinoStub->GetMode(c_pwmPin));
}

TEST(ExtruderTestGroup, setPwm)
{
   Extruder extruder(c_tempPin, c_pwmPin);
   extruder.SetTempPwmDuty(120);
   ASSERT_EQ(0, arduinoStub->GetAnalogWrite(c_pwmPin));

   extruder.SetEnabled(true);
   extruder.SetTempPwmDuty(120);
   ASSERT_EQ(120, arduinoStub->GetAnalogWrite(c_pwmPin));
}

TEST(ExtruderTestGroup, readTemp)
{
   Extruder extruder(c_tempPin, c_pwmPin);

   int expectedT = 1800;
   arduinoStub->SetAnalogPinVoltage(c_tempPin, 2.6f); // 2.6V => 180 deg C
   ASSERT_TRUE((expectedT-50 < extruder.ReadTemp()) && (extruder.ReadTemp() < expectedT+50));

   expectedT = 1940;
   arduinoStub->SetAnalogPinVoltage(c_tempPin, 2.2f); // 2.6V => 180 deg C
   ASSERT_TRUE((expectedT-50 < extruder.ReadTemp()) && (extruder.ReadTemp() < expectedT+50));

   expectedT = 2100;
   arduinoStub->SetAnalogPinVoltage(c_tempPin, 1.8f); // 2.6V => 180 deg C
   ASSERT_TRUE((expectedT-50 < extruder.ReadTemp()) && (extruder.ReadTemp() < expectedT+50));

   expectedT = 2350;
   arduinoStub->SetAnalogPinVoltage(c_tempPin, 1.2f); // 2.6V => 180 deg C
   ASSERT_TRUE((expectedT-50 < extruder.ReadTemp()) && (extruder.ReadTemp() < expectedT+50));
}

TEST(ExtruderTestGroup, setDebug)
{
   Extruder extruder(c_tempPin, c_pwmPin);

   extruder.SetDebug(0);
   ASSERT_TRUE(Serial.getData().compare(""s) == 0);

   string expected = string("extruder::debug_: 1\n");
   extruder.SetDebug(1);
   ASSERT_TRUE(Serial.getData().compare(expected) == 0);
}
}