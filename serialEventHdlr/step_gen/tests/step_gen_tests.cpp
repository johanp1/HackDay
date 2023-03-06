#include "gtest/gtest.h"
//#include "gmock/gmock.h"
#include "step_gen.h"
#include <Arduino.h>

std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();

TEST(StepGenTestGroup, test_init)
{
   StepGen s;
   ASSERT_TRUE(arduinoStub->GetMode(0) == OUTPUT);
}

// test generating one step 
// output: |"""5ms"""|___5ms___
TEST(StepGenTestGroup, test_one_step)
{
   StepGen s;

   s.Step();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(0) == PinState_High);

   arduinoStub->IncTimeMs(3);
   s.Update();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(0) == PinState_High);

   arduinoStub->IncTimeMs(3);
   s.Update();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(0) == PinState_Low);
}

// test generating two steps 
// output: |"""5ms"""|___5ms___|"""5ms"""|___5ms___
TEST(StepGenTestGroup, test_two_steps)
{
   StepGen s;

   s.Step(2);
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(0) == PinState_High);
   
   arduinoStub->IncTimeMs(5);
   s.Update();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(0) == PinState_Low);

   arduinoStub->IncTimeMs(3);
   s.Update();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(0) == PinState_Low);

   arduinoStub->IncTimeMs(2);
   s.Update();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(0) == PinState_High);
   
   arduinoStub->IncTimeMs(5);
   s.Update();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(0) == PinState_Low);
}
