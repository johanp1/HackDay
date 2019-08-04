#include "TestHarness.h"
#include "Arduino.h"
#include <string>
#include <iostream>

TEST_GROUP(ApplicationTestGroup)
{
   void run_ms(unsigned int ms)
   {
      for (int i = 0; i < int(ms / 10); i++)
      {
         ArduinoStub.Loop();
      }
   }

   void setup()
   {
      ArduinoStub.reset();
      ArduinoStub.Setup();
      ArduinoStub.clearSerialBuffer();
   }

   void teardown()
   {
      ArduinoStub.clearSerialBuffer();
   }
};
/*
TEST(ApplicationTestGroup, Startup)
{
  string expected = string("hej\n");
   ArduinoStub.Setup();
   CHECK(ArduinoStub.getSerialBuffer().compare(expected) == 0);
}

TEST(ApplicationTestGroup, Idle)
{
   ArduinoStub.Loop();
   CHECK(ArduinoStub.getSerialBuffer().compare((string)"") == 0);
}

TEST(ApplicationTestGroup, RTHButton)
{
   ArduinoStub.setDigitalRead(3, HIGH);
   run_ms(60); // one loop (10ms) for reading the first pressed button, then 50ms for the delay => 60ms
   CHECK(ArduinoStub.getSerialBuffer().compare((string)"rth_1\n") == 0);

   ArduinoStub.clearSerialBuffer();

   ArduinoStub.setDigitalRead(3, LOW);
   run_ms(60); // one loop (10ms) for reading the first pressed button, then 50ms for the delay => 60ms
   CHECK(ArduinoStub.getSerialBuffer().compare((string)"rth_0\n") == 0);
}

TEST(ApplicationTestGroup, ESTButton)
{
   ArduinoStub.setDigitalRead(8, HIGH);
   run_ms(60); // one loop (10ms) for reading the first pressed button, then 50ms for the delay => 60ms
   CHECK(ArduinoStub.getSerialBuffer().compare((string)"est_1\n") == 0);

   ArduinoStub.clearSerialBuffer();

   ArduinoStub.setDigitalRead(8, LOW);
   run_ms(60); // one loop (10ms) for reading the first pressed button, then 50ms for the delay => 60ms
   CHECK(ArduinoStub.getSerialBuffer().compare((string)"est_0\n") == 0);
}

TEST(ApplicationTestGroup, RUNButton)
{
   ArduinoStub.setDigitalRead(6, HIGH);
   run_ms(60); // one loop (10ms) for reading the first pressed button, then 50ms for the delay => 60ms
   CHECK(ArduinoStub.getSerialBuffer().compare((string)"run_1\n") == 0);

   ArduinoStub.clearSerialBuffer();

   ArduinoStub.setDigitalRead(6, LOW);
   run_ms(60); // one loop (10ms) for reading the first pressed button, then 50ms for the delay => 60ms
   CHECK(ArduinoStub.getSerialBuffer().compare((string)"run_0\n") == 0);
}

TEST(ApplicationTestGroup, AxisSelector)
{
   ArduinoStub.setAnalogRead(A3, 340);
   run_ms(120); // one loop (10ms) for reading the first time, then 100ms for the delay => 110ms
   CHECK(ArduinoStub.getSerialBuffer().compare((string)"sela_1\n") == 0);

   ArduinoStub.clearSerialBuffer();

   ArduinoStub.setAnalogRead(A3, 255);
   run_ms(120); // one loop (10ms) for reading the first time, then 100ms for the delay => 110ms
   CHECK(ArduinoStub.getSerialBuffer().compare((string)"sela_0\n") == 0);
}

TEST(ApplicationTestGroup, ScaleSelector)
{
   ArduinoStub.setAnalogRead(A2, 340);
   run_ms(120); // one loop (10ms) for reading the first time, then 100ms for the delay => 110ms
   CHECK(ArduinoStub.getSerialBuffer().compare((string)"sels_1\n") == 0);

   ArduinoStub.clearSerialBuffer();

   ArduinoStub.setAnalogRead(A2, 255);
   run_ms(120); // one loop (10ms) for reading the first time, then 100ms for the delay => 110ms
   CHECK(ArduinoStub.getSerialBuffer().compare((string)"sels_0\n") == 0);
}

TEST(ApplicationTestGroup, Rotate)
{
   const int dirPin = 7;

   // one step CW
   ArduinoStub.setDigitalRead(dirPin, HIGH);
   ArduinoStub.invokeInterrupt(HIGH);

   ArduinoStub.Loop();
   CHECK(ArduinoStub.getSerialBuffer().compare((string)"jog_1\n") == 0);

   ArduinoStub.clearSerialBuffer();

   // one step CW
   ArduinoStub.setDigitalRead(dirPin, LOW);
   ArduinoStub.invokeInterrupt(LOW);

   ArduinoStub.Loop();
   CHECK(ArduinoStub.getSerialBuffer().compare((string)"jog_2\n") == 0);

   ArduinoStub.clearSerialBuffer();

   // one step CCW
   ArduinoStub.setDigitalRead(dirPin, LOW);
   ArduinoStub.invokeInterrupt(HIGH);

   // one step CCW
   ArduinoStub.setDigitalRead(dirPin, HIGH);
   ArduinoStub.invokeInterrupt(LOW);

   ArduinoStub.Loop();
   CHECK(ArduinoStub.getSerialBuffer().compare((string)"jog_1\njog_0\n") == 0);
}
*/
/*
TEST(ApplicationTestGroup, FillUpBuffer)
{
   const int dirPin = 7;

      ArduinoStub.setDigitalRead(dirPin, HIGH);
      ArduinoStub.invokeInterrupt(HIGH);

      ArduinoStub.setDigitalRead(dirPin, LOW);
      ArduinoStub.invokeInterrupt(LOW);

      ArduinoStub.setDigitalRead(dirPin, HIGH);
      ArduinoStub.invokeInterrupt(HIGH);

   Loop();
   cout << ArduinoStub.getSerialBuffer();
   ArduinoStub.clearSerialBuffer();
}*/
