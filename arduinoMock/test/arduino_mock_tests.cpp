#include "Arduino.h"
#include <iostream>
#include "CommandLineTestRunner.h"
#include "TestHarness.h"

TEST_GROUP(ArduinoMockTestGroup)
{
   MockDigitalPin testPin;
   std::shared_ptr<ArduinoStub> arduinoStub;

   void setup()
   {  
      Serial.clear();
      arduinoStub = ArduinoStub::GetInstance();
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

TEST(ArduinoMockTestGroup, SerialPrint)
{
   Serial.print("bepa_123");
   CHECK(Serial.getData().compare("bepa_123") == 0);
}

TEST(ArduinoMockTestGroup, SerialPrintln)
{
   Serial.println("apa_321");
   CHECK(Serial.getData().compare("apa_321\n") == 0);
}

TEST(ArduinoMockTestGroup, ReadInputPin)
{
   //MockDigitalPin testPin;

   CHECK(testPin.MockGetMode() == PinMode_Input);
   testPin.MockSetDigitalRead(PinState_Low);
   CHECK(testPin.DigitalRead() == PinState_Low);

   testPin.MockSetDigitalRead(PinState_High);
   CHECK(testPin.DigitalRead() == PinState_High);
   CHECK(testPin.MockGetMode() == PinMode_Input);
}


TEST(ArduinoMockTestGroup, WriteOutputPin)
{
   //MockDigitalPin testPin;
   
   testPin.SetMode(PinMode_Output);
   CHECK(testPin.MockGetMode() == PinMode_Output);
   CHECK(testPin.MockGetDigitalWrite() == PinState_Low);

   testPin.DigitalWrite(PinState_High);
   CHECK(testPin.MockGetDigitalWrite() == PinState_High);

   testPin.DigitalWrite(PinState_Low);
   CHECK(testPin.MockGetDigitalWrite() == PinState_Low);
}

TEST(ArduinoMockTestGroup, WriteInputPin)
{
   //MockDigitalPin testPin;
   
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

   CHECK(arduinoStub->GetDigitalWrite(0) == PinState_Low);
   digitalWrite(0, HIGH);
   CHECK(arduinoStub->GetDigitalWrite(0) == PinState_High);
}

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
