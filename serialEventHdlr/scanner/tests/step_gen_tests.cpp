#include "gtest/gtest.h"
//#include "gmock/gmock.h"
#include "step_gen.h"
#include <Arduino.h>
#include <memory>
#include <iostream>
#include <sstream>

namespace {

constexpr byte test_step_pin = 1;
constexpr byte test_dir_pin = 2;
constexpr milli_sec t_on = 4;
constexpr milli_sec t_off = 10;

constexpr milli_sec t_on_test = 5;
constexpr milli_sec t_off_test = 5;

std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();

class MockStepObserver : public StepObserver
{
   public:
   void Update() override
   {
      hasBeenCalled = true;
      nbrOfCalls++;
   }

   bool hasBeenCalled = false;
   int nbrOfCalls = 0;
};

class StepGenTestFixture : public testing::Test 
{
  protected: 
   std::unique_ptr<StepGen> stepGen;
   std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();
   MockStepObserver *stepObserver;

   void SetUp()
   {
      arduinoStub->Reset();
      stepGen = std::make_unique<StepGen>(test_step_pin, test_dir_pin, t_on_test, t_off_test);
      stepObserver = new MockStepObserver;
      stepGen->Attach(stepObserver);
   }
   
   void TearDown()
   {
      stepGen.reset();
      //delete stepObserver;
   }
   
   void incTime(milli_sec t = 1)
   {
      for (uint8_t i = 0; i < t; i++)
      {
         arduinoStub->IncTimeMs(1);
         stepGen->Update();
      }
   }

   
   bool checkStep(milli_sec t_on, milli_sec t_off)
   {
      bool retVal = true;
      // check step is on for t_on ms
      for (milli_sec i = 0; i < t_on; i++)
      {
         retVal = retVal & (arduinoStub->GetDigitalWrite(test_step_pin) == PinState_High);
         incTime();

         //if (!retVal) cout << "checking step is high at pos " << i << " failed\n";
      }

      // check step is off for t_off ms
      for (milli_sec i = 0; i < t_off; i++)
      {
         retVal = retVal & (arduinoStub->GetDigitalWrite(test_step_pin) == PinState_Low);
         incTime();

         //if (!retVal) cout << "checking step is low at pos " << i + t_on << " failed\n";
      }

      return retVal;
   }
};

TEST(StepGenTestGroup, test_init)
{
   StepGen s(test_step_pin);
   ASSERT_TRUE(arduinoStub->GetMode(test_step_pin) == OUTPUT);
   ASSERT_FALSE(s.IsBusy());
}

// test generating one step 
// output: |"""5ms"""|___5ms___
TEST_F(StepGenTestFixture, test_one_step)
{
   stepGen->Step();
   ASSERT_TRUE(checkStep(t_on_test, t_off_test));
   ASSERT_TRUE(stepObserver->hasBeenCalled);
   ASSERT_FALSE(stepGen->IsBusy());
}

// test generating two steps 
// output: |"""5ms"""|___5ms___|"""5ms"""|___5ms___
TEST_F(StepGenTestFixture, test_two_steps)
{
   stepGen->Step(2);
   ASSERT_TRUE(checkStep(t_on_test, t_off_test));
   ASSERT_TRUE(stepGen->IsBusy());
   ASSERT_TRUE(checkStep(t_on_test, t_off_test));
   ASSERT_FALSE(stepGen->IsBusy());
   ASSERT_TRUE(stepObserver->nbrOfCalls == 2);
}

// test step returns busy if current step is not done
TEST(StepGenTestGroup, test_busy)
{
   StepGen s(test_step_pin, test_dir_pin, 5, 5);

   // precondition, start a step, inc time 4 ms
   ASSERT_TRUE(s.Step() == ok);  
   arduinoStub->IncTimeMs(4);
   s.Update();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_High);

   // test, try to request a new step when the last requested step is still beeing produced
   ASSERT_TRUE(s.Step() == busy); 

   arduinoStub->IncTimeMs(4);
   s.Update();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_Low);
   ASSERT_TRUE(s.Step() == busy); 

   // the step should be done now, i.e. not busy anymore
   arduinoStub->IncTimeMs(4);
   s.Update();
   ASSERT_TRUE(s.IsBusy() == false); 
}

// test step returns busy if current step is not done
TEST_F(StepGenTestFixture, test_one_step_high_freq_update)
{
   // precondition, start a step, inc time 4 ms
   ASSERT_TRUE(stepGen->Step() == ok);  
   incTime(); // 1ms
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_High);

   incTime(3); // 4ms
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_High);

   incTime(); // 5ms
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_Low);
   ASSERT_TRUE(stepGen->IsBusy()); 

   incTime(5); // 10ms
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_Low);
   ASSERT_FALSE(stepGen->IsBusy()); 
}

// test generating one step with specified speed

TEST_F(StepGenTestFixture, test_step_with_set_speed)
{
   stepGen->SetStepsPerSec(50);
   stepGen->Step(1); // with 50 steps per sec, one pulse is 20ms
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
   stepGen->SetStepsPerSec(150);
   stepGen->Step(1);
   incTime(1);
   ASSERT_TRUE(stepGen->IsBusy());
   incTime(8);
   ASSERT_TRUE(stepGen->IsBusy());
   incTime(1);
   ASSERT_FALSE(stepGen->IsBusy());
}


TEST_F(StepGenTestFixture, test_decresing_step_length_with_speed_ramp_up)
{
   stepGen->SetUseRamping(true);
   stepGen->SetStepsPerSec(100);
 
   // set nbr of steps >> max_number_of_ramp_steps not to get intervened by ramping down
   stepGen->Step(100); 
   // t_on_test + t_off_test + t_off_ramp_ - 1 (-1 means "last off-state iteration")
   // => 5 + 5 + 56 - 1 = 65
   incTime(t_on_test + t_off_test + max_t_off_ramp - 1);

   // still working on the off part of the first step
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_Low);

   incTime();
   // new step just started
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_High);

   // first step took 44 ms to finish, 2nd should be done in:
   // t_on_test + t_off_test + t_off_ramp_ - t_delta - 1 = 5 + 5 + 56 - 2 - 1 = 63
   incTime(t_on_test + t_off_test + max_t_off_ramp - 1*t_delta - 1);
   // all requested steps done
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_Low);
   //ASSERT_FALSE(stepGen->IsBusy());
   incTime();
   // new step just started
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_High);

   // 3nd should be done in:
   // t_on_test + t_off_test + t_off_ramp_ - 2*t_delta - 1 = 5 + 5 + 56 - 4 - 1 = 61
   incTime(t_on_test + t_off_test + max_t_off_ramp - 2*t_delta - 1);
   // all requested steps done
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_Low);
   //ASSERT_FALSE(stepGen->IsBusy());
   incTime();
   // new step just started
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_High);
}

TEST_F(StepGenTestFixture, test_decresing_step)
{
   stepGen->SetUseRamping(true);
   stepGen->SetStepsPerSec(100);
   
   milli_sec ramp_steps = max_number_of_ramp_steps;

   // set nbr of steps >> max_number_of_ramp_steps not to get intervened by ramping down
   stepGen->Step(100); 

   for (int8_t i = 0; i < ramp_steps; i++)
   {
      ASSERT_TRUE(checkStep(t_on_test, t_off_test + t_delta*(ramp_steps-i)));
   }
}

TEST_F(StepGenTestFixture, test_incresing_step_length_with_speed_ramp_down)
{
   stepGen->SetUseRamping(true);
   stepGen->SetStepsPerSec(100);
   
   milli_sec ramp_steps = max_number_of_ramp_steps;

   // set nbr of steps to get full ramp up, one steady state step then full ramp down
   stepGen->Step(2 * max_number_of_ramp_steps + 1); 

   // ramping up
   for (int8_t i = 0; i < ramp_steps; i++)
   {
      //cout << "checking ramp up step " << to_string(i) << (checkStep(t_on_test, t_off_test + (ramp_steps-i)) ? "OK":"fail") << "\n";
      ASSERT_TRUE(checkStep(t_on_test, t_off_test + t_delta*(ramp_steps-i)));
   }

   // one max speed step
   //cout << "checking steady state step " << (checkStep(t_on_test, t_off_test) ? "OK":"fail") << "\n";
   ASSERT_TRUE(checkStep(t_on_test, t_off_test));

   // ramping down
   for (int8_t i = 1; i < ramp_steps; i++)
   {
      //cout << "checking ramp down step " << to_string(i) << (checkStep(t_on_test, t_off_test + i) ? "OK":"fail") << "\n";
      ASSERT_TRUE(checkStep(t_on_test, t_off_test + t_delta*i));
   }
}

TEST_F(StepGenTestFixture, test_incomlpete_ramping)
{
   stepGen->SetUseRamping(true);
   stepGen->SetStepsPerSec(100);
   
   milli_sec ramp_steps = 20; // made up number
   uint16_t requested_steps = 2 * ramp_steps;

   // set nbr of steps to get incomplete ramp up, straight in to incomplete ramp down
   // never reaching full speed
   stepGen->Step(requested_steps);  // hopefully this gives 20 ramp up, 20 ramp down

   // ramping up
   for (int8_t i = 0; i < ramp_steps; i++)
   {
      // cout << "checking ramp up step " << to_string(requested_steps-1-i) << ", t_on " << t_on_test << " , t_off " << t_off_test + (max_number_of_ramp_steps-i) << "\n";
      // cout << (checkStep(t_on_test, t_off_test + (max_number_of_ramp_steps-i)) ? "OK":"fail") << "\n";
      ASSERT_TRUE(checkStep(t_on_test, t_off_test + t_delta*(max_number_of_ramp_steps-i)));
   }

   // ramping down
   for (int8_t i = 0; i < ramp_steps; i++)
   {
      // cout << "checking ramp down step " << to_string(ramp_steps-1-i) << ", t_on " << t_on_test << " , t_off " << t_off_test + (max_number_of_ramp_steps-ramp_steps) + t_delta*i << "\n";
      // cout << (checkStep(t_on_test, t_off_test + t_delta*(max_number_of_ramp_steps - ramp_steps + i)) ? "OK":"fail") << "\n";
      ASSERT_TRUE(checkStep(t_on_test, t_off_test + t_delta*(max_number_of_ramp_steps - ramp_steps + i)));
   }
}

TEST_F(StepGenTestFixture, test_direction)
{
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_dir_pin) == LOW);

   stepGen->SetDirection(direction_reverse);
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_dir_pin) == HIGH);
   ASSERT_TRUE(stepGen->GetDirection() == direction_reverse);

   stepGen->SetDirection(direction_forward);
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_dir_pin) == LOW);
   ASSERT_TRUE(stepGen->GetDirection() == direction_forward);
}

TEST(StepGenTestGroup, test_direction_flipped)
{
   StepGen s(test_step_pin, test_dir_pin, 5, 5, true);

   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_dir_pin) == HIGH);

   s.SetDirection(direction_reverse);
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_dir_pin) == LOW);
   ASSERT_TRUE(s.GetDirection() == direction_reverse);

   s.SetDirection(direction_forward);
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_dir_pin) == HIGH);
   ASSERT_TRUE(s.GetDirection() == direction_forward);
}

}