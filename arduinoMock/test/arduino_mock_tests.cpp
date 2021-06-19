#include "Arduino.h"
#include <iostream>
#include "CommandLineTestRunner.h"
#include "TestHarness.h"

TEST_GROUP(ArduinoMockTestGroup)
{
   std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();

   void setup()
   {  
      Serial.clear();
      arduinoStub->Reset();
   }
   
   void teardown()
   {
   }
};

TEST(ArduinoMockTestGroup, Init)
{
   CHECK(arduinoStub->GetMode(0) == PinMode_Input);
   CHECK(arduinoStub->GetMode(1) == PinMode_Input);
   CHECK(arduinoStub->GetMode(2) == PinMode_Input);
   CHECK(arduinoStub->GetMode(3) == PinMode_Input);
   CHECK(arduinoStub->GetMode(4) == PinMode_Input);
   CHECK(arduinoStub->GetMode(5) == PinMode_Input);
   CHECK(arduinoStub->GetMode(6) == PinMode_Input);
   CHECK(arduinoStub->GetMode(7) == PinMode_Input);
   CHECK(arduinoStub->GetMode(8) == PinMode_Input);

   CHECK(Serial.available() == 0);
}

// test all overloads of Serial.print
TEST(ArduinoMockTestGroup, SerialPrint)
{
   String test_string = String("test");
   Serial.print(test_string);
   CHECK(Serial.getData().compare("test") == 0);

   Serial.print("bepa_123");
   CHECK(Serial.getData().compare("bepa_123") == 0);

   Serial.print(987);
   CHECK(Serial.getData().compare("987") == 0);
}

// test all overloads of Serial.println
TEST(ArduinoMockTestGroup, SerialPrintln)
{
   String test_string = String("tset");
   Serial.print(test_string);
   CHECK(Serial.getData().compare("tset") == 0);

   Serial.println("apa_321");
   CHECK(Serial.getData().compare("apa_321\n") == 0);

   Serial.println(789);
   CHECK(Serial.getData().compare("789\n") == 0);
}

TEST(ArduinoMockTestGroup, ReadInputPin)
{
   MockDigitalPin testPin;

   CHECK(testPin.MockGetMode() == PinMode_Input);
   testPin.MockSetDigitalRead(PinState_Low);
   CHECK(testPin.DigitalRead() == PinState_Low);

   testPin.MockSetDigitalRead(PinState_High);
   CHECK(testPin.DigitalRead() == PinState_High);
   CHECK(testPin.MockGetMode() == PinMode_Input);
}


TEST(ArduinoMockTestGroup, WriteOutputPin)
{
   MockDigitalPin testPin;
   
   testPin.SetMode(PinMode_Output);
   CHECK(testPin.MockGetMode() == PinMode_Output);
   CHECK(testPin.MockGetDigitalWrite() == PinState_Low);

   testPin.DigitalWrite(PinState_High);
   CHECK(testPin.MockGetDigitalWrite() == PinState_High);

   testPin.DigitalWrite(PinState_Low);
   CHECK(testPin.MockGetDigitalWrite() == PinState_Low);
}

TEST(ArduinoMockTestGroup, AnalogWritePin)
{
   MockDigitalPin testPin;
   
   CHECK(testPin.MockGetAnalogWrite() == 0);

   testPin.AnalogWrite(100);
   CHECK(testPin.MockGetAnalogWrite() == 100);
}

TEST(ArduinoMockTestGroup, WriteInputPin)
{
   MockDigitalPin testPin;
   
   CHECK(testPin.MockGetMode() == PinMode_Input);
   CHECK(testPin.MockGetDigitalWrite() == PinState_Low);

   testPin.DigitalWrite(PinState_High);
   CHECK(testPin.MockGetDigitalWrite() == PinState_High);
   CHECK(testPin.MockGetMode() == PinMode_InputPullUp);
}


TEST(ArduinoMockTestGroup, ArduinoReadInputPin)
{
   CHECK(digitalRead(0) == LOW);
   arduinoStub->SetDigitalRead(0, PinState_High);
   CHECK(digitalRead(0) == HIGH);
}

TEST(ArduinoMockTestGroup, ArduinoWriteOutputPin)
{
   pinMode(0, OUTPUT);
   CHECK(arduinoStub->GetMode(0) == OUTPUT);
   CHECK(arduinoStub->GetDigitalWrite(0) == PinState_Low);
   digitalWrite(0, HIGH);
   CHECK(arduinoStub->GetDigitalWrite(0) == PinState_High);
}

TEST(ArduinoMockTestGroup, ArduinoAnalogWritePin)
{
   CHECK(arduinoStub->GetAnalogWrite(0) == 0);
   analogWrite(0, 250);
   CHECK(arduinoStub->GetAnalogWrite(0) == 250);
}

// check that nothing catastrophic happens if index outside of bounds
TEST(ArduinoMockTestGroup, ArduinoDigitalPinOutOfBound)
{
   CHECK_THROWS(out_of_range, digitalWrite(9, HIGH));
   CHECK_THROWS(out_of_range, digitalRead(9));
   CHECK_THROWS(out_of_range, pinMode(9, OUTPUT));
}

TEST(ArduinoMockTestGroup, ReadAnalogPinBasic)
{
   MockAnalogPin testPin;

   CHECK(testPin.AnalogRead() == 0);

   testPin.SetAnalogVoltage(5);
   CHECK(testPin.AnalogRead() == 1023);

   testPin.SetAnalogVoltage(0);
   CHECK(testPin.AnalogRead() == 0);

   testPin.SetAnalogVoltage(1.2f);
   CHECK(testPin.AnalogRead() ==  (unsigned int)(1023*1.2/5));

   testPin.SetAnalogVoltage(5.5f);
   CHECK(testPin.AnalogRead() == 1023);
}

TEST(ArduinoMockTestGroup, ReadAnalogPinReferenceResolution)
{
   MockAnalogPin testPin(12, 3.3f);

   CHECK(testPin.AnalogRead() == 0);

   testPin.SetAnalogVoltage(3.3f);
   CHECK(testPin.AnalogRead() == 4095);
}

TEST(ArduinoMockTestGroup, ArduinoReadAnalogPin)
{
   CHECK(analogRead(0) == 0);
   arduinoStub->SetAnalogPinVoltage(0, 2.5f);
   CHECK(analogRead(0) == (unsigned int)(1023*2.5f/5));
}

// check that nothing catastrophic happens if index outside of bounds
TEST(ArduinoMockTestGroup, ArduinoAnalogPinOutOfBound)
{
   CHECK_THROWS(out_of_range, analogRead(4));
}

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
