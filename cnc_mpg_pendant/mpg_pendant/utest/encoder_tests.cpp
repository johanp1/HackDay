#include "TestHarness.h"
#include "encoder.h"
#include "Arduino.h"

#define CLK_PIN 1
#define DT_PIN 2

TEST_GROUP(EncoderTestGroup)
{
  C_RotaryEncoder* e;
  
  void setup()
  {
    ArduinoStub.reset();
    e = new C_RotaryEncoder("enc", CLK_PIN, DT_PIN);
  }
  
  void teardown()
  {
    delete e;
  }

};

TEST(EncoderTestGroup, Init)
{
  LONGS_EQUAL(INPUT, ArduinoStub.getMode(CLK_PIN));
  LONGS_EQUAL(INPUT, ArduinoStub.getMode(DT_PIN));
  LONGS_EQUAL(HIGH, ArduinoStub.getDigitalWrite(CLK_PIN));
  LONGS_EQUAL(HIGH, ArduinoStub.getDigitalWrite(DT_PIN));
}

TEST(EncoderTestGroup, NoMovement)
{
  LONGS_EQUAL(0, e->getPosition());
}
 
TEST(EncoderTestGroup, MoveOneStepClkPosFlankCW)
{
  ArduinoStub.setDigitalRead(CLK_PIN, HIGH);
  ArduinoStub.setDigitalRead(DT_PIN, HIGH);
  e->update();
  LONGS_EQUAL(1, e->getPosition());
}

TEST(EncoderTestGroup, MoveOneStepClkPosFlankCCW)
{
  ArduinoStub.setDigitalRead(CLK_PIN, HIGH);
  ArduinoStub.setDigitalRead(DT_PIN, LOW);
  e->update();
  LONGS_EQUAL(-1, e->getPosition());
}

TEST(EncoderTestGroup, MoveOneStepClkNegFlankCW)
{
  ArduinoStub.setDigitalRead(CLK_PIN, LOW);
  ArduinoStub.setDigitalRead(DT_PIN, LOW);
  e->update();
  LONGS_EQUAL(1, e->getPosition());
}

TEST(EncoderTestGroup, MoveOneStepClkNegFlankCCW)
{
  ArduinoStub.setDigitalRead(CLK_PIN, LOW);
  ArduinoStub.setDigitalRead(DT_PIN, HIGH);
  e->update();
  LONGS_EQUAL(-1, e->getPosition());
}
