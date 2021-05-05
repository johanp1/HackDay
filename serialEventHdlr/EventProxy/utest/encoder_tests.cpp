#include "TestHarness.h"
#include "encoder.h"
#include "Arduino.h"
#include <memory>

#define CLK_PIN 1
#define DT_PIN 2

TEST_GROUP(EncoderTestGroup)
{
  std::unique_ptr<RotaryEncoder> e;
  std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();

   void setup()
   {
      arduinoStub->Reset();
      e = std::make_unique<RotaryEncoder>("enc", CLK_PIN, DT_PIN);
   }
  
   void teardown()
   {
      e.reset();
   }

};

TEST(EncoderTestGroup, Init)
{
  LONGS_EQUAL(INPUT_PULLUP, arduinoStub->GetMode(CLK_PIN));
  LONGS_EQUAL(INPUT_PULLUP, arduinoStub->GetMode(DT_PIN));
  LONGS_EQUAL(HIGH, arduinoStub->GetDigitalWrite(CLK_PIN));
  LONGS_EQUAL(HIGH, arduinoStub->GetDigitalWrite(DT_PIN));
}

TEST(EncoderTestGroup, NoMovement)
{
  LONGS_EQUAL(0, e->getPosition());
}
 
TEST(EncoderTestGroup, MoveOneStepClkPosFlankCW)
{
  arduinoStub->SetDigitalRead(CLK_PIN, HIGH);
  arduinoStub->SetDigitalRead(DT_PIN, HIGH);
  e->update();
  LONGS_EQUAL(1, e->getPosition());
}

TEST(EncoderTestGroup, MoveOneStepClkPosFlankCCW)
{
  arduinoStub->SetDigitalRead(CLK_PIN, HIGH);
  arduinoStub->SetDigitalRead(DT_PIN, LOW);
  e->update();
  LONGS_EQUAL(-1, e->getPosition());
}
