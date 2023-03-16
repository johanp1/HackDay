#include "gtest/gtest.h"
//#include "gmock/gmock.h"
#include "step_gen.h"
#include <Arduino.h>
#include <memory>

namespace {
constexpr byte test_pin = 1;
constexpr milli_sec t_on = 4;
constexpr milli_sec t_off = 10;

std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();



class StepGenTestFixture : public testing::Test 
{
  protected: 
   std::unique_ptr<StepGen> stepGen;
   std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();

   void SetUp()
   {
      arduinoStub->Reset();
      stepGen = std::make_unique<StepGen>(test_pin, 5, 5);
   }
   
   void TearDown()
   {
      stepGen.reset();
   }
   
   void incTime(milli_sec t = 1)
   {
      for (uint8_t i = 0; i < t; i++)
      {
         arduinoStub->IncTimeMs(1);
         stepGen->Update();
      }
   }
};

TEST(StepGenTestGroup, test_init)
{
   StepGen s(test_pin);
   ASSERT_TRUE(arduinoStub->GetMode(test_pin) == OUTPUT);
}

// test generating one step 
// output: |"""5ms"""|___5ms___
TEST(StepGenTestGroup, test_one_step)
{
   StepGen s(test_pin, 5, 5);

   s.Step();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_High);

   arduinoStub->IncTimeMs(3);
   s.Update();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_High);

   arduinoStub->IncTimeMs(3);
   s.Update();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_Low);
}

// test generating two steps 
// output: |"""5ms"""|___5ms___|"""5ms"""|___5ms___
TEST(StepGenTestGroup, test_two_steps)
{
   StepGen s(test_pin, 5, 5);

   s.Step(2);
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_High);
   
   arduinoStub->IncTimeMs(5);
   s.Update();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_Low);

   arduinoStub->IncTimeMs(3);
   s.Update();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_Low);

   arduinoStub->IncTimeMs(2);
   s.Update();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_High);
   
   arduinoStub->IncTimeMs(5);
   s.Update();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_Low);

   // make check no new step is started
   arduinoStub->IncTimeMs(5);
   s.Update();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_Low);
}

// test step returns busy if current step is not done
TEST(StepGenTestGroup, test_busy)
{
   StepGen s(test_pin, 5, 5);

   // precondition, start a step, inc time 4 ms
   ASSERT_TRUE(s.Step() == ok);  
   arduinoStub->IncTimeMs(4);
   s.Update();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_High);

   // test, try to request a new step when the last requested step is still beeing produced
   ASSERT_TRUE(s.Step() == busy); 

   arduinoStub->IncTimeMs(4);
   s.Update();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_Low);
   ASSERT_TRUE(s.Step() == busy); 

   // the step should be done now, i.e. not busy anymore
   arduinoStub->IncTimeMs(4);
   s.Update();
   ASSERT_TRUE(s.IsBusy() == false); 
}

// test step returns busy if current step is not done
TEST_F(StepGenTestFixture, test_one_step_high_freq_update)
{
   StepGen s(test_pin, t_on, t_off);

   // precondition, start a step, inc time 4 ms
   ASSERT_TRUE(stepGen->Step() == ok);  
   incTime(); // 1ms
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_High);

   incTime(3); // 4ms
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_High);

   incTime(); // 5ms
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_Low);

   incTime(8); // 13ms
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_Low);

   incTime(); // 14ms
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_Low);
   ASSERT_TRUE(s.IsBusy() == false); 
}

// test generating one step with specified speed

TEST_F(StepGenTestFixture, test_step_with_set_speed)
{
   stepGen->Step(1, 50); // with 50 steps per sec, one pulse is 20ms
   incTime(1);
   ASSERT_TRUE(stepGen->IsBusy());
   incTime(18);
   ASSERT_TRUE(stepGen->IsBusy());
   incTime(1);
   ASSERT_FALSE(stepGen->IsBusy());
}

// test generating one step with specified speed
// stepGen is set up to have max speed of 100 steps / sec
TEST_F(StepGenTestFixture, test_step_with_to_high_speed)
{
   // given t_on + t_off, highest possibler speed is 100 pps
   // test speed saturated if above
   stepGen->Step(1, 150);
   incTime(1);
   ASSERT_TRUE(stepGen->IsBusy());
   incTime(8);
   ASSERT_TRUE(stepGen->IsBusy());
   incTime(1);
   ASSERT_FALSE(stepGen->IsBusy());
}
/*
TEST_F(StepGenTestFixture, test_decresing_step_length_with_speed_ramp_up)
{
   stepGen->Step(2, true);
   incTime(39);

   // still working on the off part of the first step
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_Low);

   incTime();
   // new step just started
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_High);

   // first step took 40 ms to finish, 2nd should be done in 39
   incTime(39);
   // all requested steps done
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_pin) == PinState_Low);
   ASSERT_FALSE(stepGen->IsBusy());
  
}
 */
}