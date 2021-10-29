#include "encoder.h"
#include "Arduino.h"
#include <memory>
#include <gtest/gtest.h>

#define CLK_PIN 1
#define DT_PIN 2

namespace {
class EncoderTestFixture : public testing::Test 
{
  protected: 
   std::unique_ptr<RotaryEncoder> e;
   std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();

   void SetUp()
   {
      arduinoStub->Reset();
      e = std::make_unique<RotaryEncoder>("enc", CLK_PIN, DT_PIN);
   }
   
   void TearDown()
   {
      e.reset();
   }
};

TEST_F(EncoderTestFixture, Init)
{
   ASSERT_TRUE(INPUT_PULLUP == arduinoStub->GetMode(CLK_PIN));
   ASSERT_TRUE(INPUT_PULLUP == arduinoStub->GetMode(DT_PIN));
   ASSERT_TRUE(HIGH == arduinoStub->GetDigitalWrite(CLK_PIN));
   ASSERT_TRUE(HIGH == arduinoStub->GetDigitalWrite(DT_PIN));
}

TEST_F(EncoderTestFixture, NoMovement)
{
   ASSERT_TRUE(0 == e->getPosition());
}
 
TEST_F(EncoderTestFixture, MoveOneStepClkPosFlankCW)
{
   arduinoStub->SetDigitalRead(CLK_PIN, HIGH);
   arduinoStub->SetDigitalRead(DT_PIN, HIGH);
   e->update();
   ASSERT_TRUE(1 == e->getPosition());
}

TEST_F(EncoderTestFixture, MoveOneStepClkPosFlankCCW)
{
   arduinoStub->SetDigitalRead(CLK_PIN, HIGH);
   arduinoStub->SetDigitalRead(DT_PIN, LOW);
   e->update();
   ASSERT_TRUE(-1 == e->getPosition());
}
} // namespace