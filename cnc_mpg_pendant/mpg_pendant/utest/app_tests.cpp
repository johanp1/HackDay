#include "TestHarness.h"
#include "Arduino.h"
#include <string>
#include <iostream>
#include "encoder.h"
#include "mpg_pendant.h"

extern C_RotaryEncoder encoder;

TEST_GROUP(ApplicationTestGroup)
{
   void run_ms(unsigned int ms)
   {
      for (int i = 0; i < int(ms / LOOP_DELAY_TIME); i++)
      {
         ArduinoStub.Loop();
      }
   }

   void setup()
   {
      ArduinoStub.reset();
      ArduinoStub.Setup();
      
      Serial.clear();
   }

   void teardown()
   {
      Serial.clear();
   }
};

TEST(ApplicationTestGroup, Startup)
{
  string expected = string("hej\n");
   ArduinoStub.Setup();
   CHECK(Serial.getData().compare(expected) == 0);
}

TEST(ApplicationTestGroup, Idle)
{
   string emptyString = string("");
   ArduinoStub.Loop();
   CHECK(Serial.getData().compare(emptyString) == 0);
}

TEST(ApplicationTestGroup, RTHButton)
{
   string expected = string("rth_1\n");

   ArduinoStub.setDigitalRead(RTH_BUTTON_PIN, HIGH);
   run_ms(60); // one loop (10ms) for reading the first pressed button, then 50ms for the delay => 60ms
   CHECK(Serial.getData().compare(expected) == 0);

   Serial.clear();

   expected.assign("rth_0\n");
   ArduinoStub.setDigitalRead(RTH_BUTTON_PIN, LOW);
   run_ms(60); // one loop (10ms) for reading the first pressed button, then 50ms for the delay => 60ms
   CHECK(Serial.getData().compare(expected) == 0);
}

TEST(ApplicationTestGroup, ESTButton)
{
   string expected = string("est_1\n");

   ArduinoStub.setDigitalRead(EST_BUTTON_PIN, HIGH);
   run_ms(60); // one loop (10ms) for reading the first pressed button, then 50ms for the delay => 60ms
   CHECK(Serial.getData().compare(expected) == 0);

   Serial.clear();

   expected.assign("est_0\n");
   ArduinoStub.setDigitalRead(EST_BUTTON_PIN, LOW);
   run_ms(60); // one loop (10ms) for reading the first pressed button, then 50ms for the delay => 60ms
   CHECK(Serial.getData().compare(expected) == 0);
}

TEST(ApplicationTestGroup, RUNButton)
{
   string expected = string("run_1\n");
   
   ArduinoStub.setDigitalRead(RUN_BUTTON_PIN, HIGH);
   run_ms(60); // one loop (10ms) for reading the first pressed button, then 50ms for the delay => 60ms
   CHECK(Serial.getData().compare(expected) == 0);

   Serial.clear();

   expected.assign("run_0\n");
   ArduinoStub.setDigitalRead(RUN_BUTTON_PIN, LOW);
   run_ms(60); // one loop (10ms) for reading the first pressed button, then 50ms for the delay => 60ms
   CHECK(Serial.getData().compare(expected) == 0);
}

TEST(ApplicationTestGroup, AxisSelector)
{
   string expected = string("sela_1\n");

   ArduinoStub.setAnalogRead(AXIS_SELECTOR_PIN, 340);
   run_ms(120); // one loop (10ms) for reading the first time, then 100ms for the delay => 110ms
   CHECK(Serial.getData().compare(expected) == 0);

   Serial.clear();

   expected.assign("sela_0\n");
   ArduinoStub.setAnalogRead(AXIS_SELECTOR_PIN, 255);
   run_ms(120); // one loop (10ms) for reading the first time, then 100ms for the delay => 110ms
   CHECK(Serial.getData().compare(expected) == 0);
}

TEST(ApplicationTestGroup, ScaleSelector)
{
   string expected = string("sels_1\n");

   ArduinoStub.setAnalogRead(SCALE_SELECTOR_PIN, 340);
   run_ms(120); // one loop (10ms) for reading the first time, then 100ms for the delay => 110ms
   CHECK(Serial.getData().compare(expected) == 0);

   Serial.clear();

   expected.assign("sels_0\n");
   ArduinoStub.setAnalogRead(SCALE_SELECTOR_PIN, 255);
   run_ms(120); // one loop (10ms) for reading the first time, then 100ms for the delay => 110ms
   CHECK(Serial.getData().compare(expected) == 0);
}

TEST(ApplicationTestGroup, Rotate)
{
   string expected = string("jog_1\n");
   
   // one step CW
   ArduinoStub.setDigitalRead(ENCODER_DT_PIN, HIGH);
   ArduinoStub.invokeInterrupt(HIGH);

   ArduinoStub.Loop();
   CHECK(Serial.getData().compare(expected) == 0);

   Serial.clear();

   expected.assign("jog_2\n");
   // one step CW
   ArduinoStub.setDigitalRead(ENCODER_DT_PIN, LOW);
   ArduinoStub.invokeInterrupt(LOW);

   ArduinoStub.Loop();
   CHECK(Serial.getData().compare(expected) == 0);

   Serial.clear();
  
   expected.assign("jog_1\njog_0\n");
   // one step CCW
   ArduinoStub.setDigitalRead(ENCODER_DT_PIN, LOW);
   ArduinoStub.invokeInterrupt(HIGH);

   // one step CCW
   ArduinoStub.setDigitalRead(ENCODER_DT_PIN, HIGH);
   ArduinoStub.invokeInterrupt(LOW);

   ArduinoStub.Loop();
   CHECK(Serial.getData().compare(expected) == 0);
}


TEST(ApplicationTestGroup, FillUpBuffer)
{
   string expected = string("jog_1\njog_2\njog_3\n");

      ArduinoStub.setDigitalRead(ENCODER_DT_PIN, HIGH);
      ArduinoStub.invokeInterrupt(HIGH);

      ArduinoStub.setDigitalRead(ENCODER_DT_PIN, LOW);
      ArduinoStub.invokeInterrupt(LOW);

      ArduinoStub.setDigitalRead(ENCODER_DT_PIN, HIGH);
      ArduinoStub.invokeInterrupt(HIGH);

   ArduinoStub.Loop();
//   cout << Serial.getData();
   CHECK(Serial.getData().compare(expected) == 0);
   Serial.clear();
}
