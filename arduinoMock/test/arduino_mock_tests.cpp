#include "CommandLineTestRunner.h"
#include "TestHarness.h"
#include "Arduino.h"

TEST_GROUP(ArduinoMockTestGroup)
{
  void setup()
  {  
     Serial.clear();
  }
  
  void teardown()
  {
  }
};

TEST(ArduinoMockTestGroup, Init)
{
   CHECK(ArduinoStub.getMode(0) == PinMode_Output);
   CHECK(ArduinoStub.getMode(1) == PinMode_Output);
   CHECK(ArduinoStub.getMode(2) == PinMode_Output);
   CHECK(ArduinoStub.getMode(3) == PinMode_Output);
   CHECK(ArduinoStub.getMode(4) == PinMode_Output);
   CHECK(ArduinoStub.getMode(5) == PinMode_Output);
   CHECK(ArduinoStub.getMode(6) == PinMode_Output);
   CHECK(ArduinoStub.getMode(7) == PinMode_Output);
   CHECK(true);
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
   MockDigitalPin testPin;

   CHECK(testPin.mockGetMode() == PinMode_Input);
   testPin.mockSetDigitalRead(PinState_Low);
   CHECK(testPin.digitalRead() == PinState_Low);
}


TEST(ArduinoMockTestGroup, WriteOutputPin)
{
   MockDigitalPin testPin;
   
   testPin.setMode(PinMode_Output);
   CHECK(testPin.mockGetMode() == PinMode_Output);
   CHECK(testPin.mockGetDigitalWrite() == PinState_Low);

   testPin.digitalWrite(PinState_High);
   CHECK(testPin.mockGetDigitalWrite() == PinState_High);

   testPin.digitalWrite(PinState_Low);
   CHECK(testPin.mockGetDigitalWrite() == PinState_Low);
}

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
