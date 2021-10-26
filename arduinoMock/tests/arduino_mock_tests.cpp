#include "Arduino.h"
#include <iostream>
#include <gtest/gtest.h>

using namespace arduino_stub;

std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();

void setup()
{  
   Serial.clear();
   arduinoStub->Reset();
}
   
void teardown()
{
}


TEST(ArduinoMockTestGroup, Init)
{
   ASSERT_TRUE(arduinoStub->GetMode(0) == PinMode_Input);
   ASSERT_TRUE(arduinoStub->GetMode(1) == PinMode_Input);
   ASSERT_TRUE(arduinoStub->GetMode(2) == PinMode_Input);
   ASSERT_TRUE(arduinoStub->GetMode(3) == PinMode_Input);
   ASSERT_TRUE(arduinoStub->GetMode(4) == PinMode_Input);
   ASSERT_TRUE(arduinoStub->GetMode(5) == PinMode_Input);
   ASSERT_TRUE(arduinoStub->GetMode(6) == PinMode_Input);
   ASSERT_TRUE(arduinoStub->GetMode(7) == PinMode_Input);
   ASSERT_TRUE(arduinoStub->GetMode(8) == PinMode_Input);

   ASSERT_TRUE(Serial.available() == 0);
}

// test all overloads of Serial.print
TEST(ArduinoMockTestGroup, SerialPrint)
{
   String test_string = String("test");
   Serial.print(test_string);
   ASSERT_TRUE(Serial.getData().compare("test") == 0);

   Serial.print("bepa_123");
   ASSERT_TRUE(Serial.getData().compare("bepa_123") == 0);

   Serial.print(987);
   ASSERT_TRUE(Serial.getData().compare("987") == 0);
}

// test all overloads of Serial.println
TEST(ArduinoMockTestGroup, SerialPrintln)
{
   String test_string = String("tset");
   Serial.print(test_string);
   ASSERT_TRUE(Serial.getData().compare("tset") == 0);

   Serial.println("apa_321");
   ASSERT_TRUE(Serial.getData().compare("apa_321\n") == 0);

   Serial.println(789);
   ASSERT_TRUE(Serial.getData().compare("789\n") == 0);
}

TEST(ArduinoMockTestGroup, ReadInputPin)
{
   MockDigitalPin testPin;

   ASSERT_TRUE(testPin.MockGetMode() == PinMode_Input);
   testPin.MockSetDigitalRead(PinState_Low);
   ASSERT_TRUE(testPin.DigitalRead() == PinState_Low);

   testPin.MockSetDigitalRead(PinState_High);
   ASSERT_TRUE(testPin.DigitalRead() == PinState_High);
   ASSERT_TRUE(testPin.MockGetMode() == PinMode_Input);
}


TEST(ArduinoMockTestGroup, WriteOutputPin)
{
   MockDigitalPin testPin;
   
   testPin.SetMode(PinMode_Output);
   ASSERT_TRUE(testPin.MockGetMode() == PinMode_Output);
   ASSERT_TRUE(testPin.MockGetDigitalWrite() == PinState_Low);

   testPin.DigitalWrite(PinState_High);
   ASSERT_TRUE(testPin.MockGetDigitalWrite() == PinState_High);

   testPin.DigitalWrite(PinState_Low);
   ASSERT_TRUE(testPin.MockGetDigitalWrite() == PinState_Low);
}

TEST(ArduinoMockTestGroup, AnalogWritePin)
{
   MockDigitalPin testPin;
   
   ASSERT_TRUE(testPin.MockGetAnalogWrite() == 0);

   testPin.AnalogWrite(100);
   ASSERT_TRUE(testPin.MockGetAnalogWrite() == 100);
}

TEST(ArduinoMockTestGroup, WriteInputPin)
{
   MockDigitalPin testPin;
   
   ASSERT_TRUE(testPin.MockGetMode() == PinMode_Input);
   ASSERT_TRUE(testPin.MockGetDigitalWrite() == PinState_Low);

   testPin.DigitalWrite(PinState_High);
   ASSERT_TRUE(testPin.MockGetDigitalWrite() == PinState_High);
   ASSERT_TRUE(testPin.MockGetMode() == PinMode_InputPullUp);
}


TEST(ArduinoMockTestGroup, ArduinoReadInputPin)
{
   ASSERT_TRUE(digitalRead(0) == LOW);
   arduinoStub->SetDigitalRead(0, PinState_High);
   ASSERT_TRUE(digitalRead(0) == HIGH);
}

TEST(ArduinoMockTestGroup, ArduinoWriteOutputPin)
{
   pinMode(0, OUTPUT);
   ASSERT_TRUE(arduinoStub->GetMode(0) == OUTPUT);
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(0) == PinState_Low);
   digitalWrite(0, HIGH);
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(0) == PinState_High);
}

TEST(ArduinoMockTestGroup, ArduinoAnalogWritePin)
{
   ASSERT_TRUE(arduinoStub->GetAnalogWrite(0) == 0);
   analogWrite(0, 250);
   ASSERT_TRUE(arduinoStub->GetAnalogWrite(0) == 250);
}

// check that nothing catastrophic happens if index outside of bounds
TEST(ArduinoMockTestGroup, ArduinoDigitalPinOutOfBound)
{
/*   CHECK_THROWS(out_of_range, digitalWrite(9, HIGH));
   CHECK_THROWS(out_of_range, digitalRead(9));
   CHECK_THROWS(out_of_range, pinMode(9, OUTPUT));*/
}

TEST(ArduinoMockTestGroup, ReadAnalogPinBasic)
{
   MockAnalogPin testPin;

   ASSERT_TRUE(testPin.AnalogRead() == 0);

   testPin.SetAnalogVoltage(5);
   ASSERT_TRUE(testPin.AnalogRead() == 1023);

   testPin.SetAnalogVoltage(0);
   ASSERT_TRUE(testPin.AnalogRead() == 0);

   testPin.SetAnalogVoltage(1.2f);
   ASSERT_TRUE(testPin.AnalogRead() ==  (unsigned int)(1023*1.2/5));

   testPin.SetAnalogVoltage(5.5f);
   ASSERT_TRUE(testPin.AnalogRead() == 1023);
}

TEST(ArduinoMockTestGroup, ReadAnalogPinReferenceResolution)
{
   MockAnalogPin testPin(12, 3.3f);

   ASSERT_TRUE(testPin.AnalogRead() == 0);

   testPin.SetAnalogVoltage(3.3f);
   ASSERT_TRUE(testPin.AnalogRead() == 4095);
}

TEST(ArduinoMockTestGroup, ArduinoReadAnalogPin)
{
   ASSERT_TRUE(analogRead(0) == 0);
   arduinoStub->SetAnalogPinVoltage(0, 2.5f);
   ASSERT_TRUE(analogRead(0) == (unsigned int)(1023*2.5f/5));
}

// check that nothing catastrophic happens if index outside of bounds
TEST(ArduinoMockTestGroup, ArduinoAnalogPinOutOfBound)
{
   //CHECK_THROWS(out_of_range, analogRead(4));
}

/*
int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
*/

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}