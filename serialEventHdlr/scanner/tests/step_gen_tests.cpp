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

constexpr micro_sec t_on_test = 1000;
constexpr micro_sec t_off_test = 1000;

constexpr unsigned long kDefaultMaxTOffRamp = default_number_of_ramp_steps * default_t_delta; 

constexpr micro_sec periodicity = 250; // us

class MockStepObserver;

std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();

class MockStepObserver : public StepObserver
{
   public:
   void Reset()
   {
      hasBeenCalled = false;
      nbrOfCalls = 0;
   }

   static void UpdateWrapper(MockStepObserver* o)
   {
      if (o != nullptr)
      {
         o->hasBeenCalled = true;
         o->nbrOfCalls++;
      }
   }

   bool hasBeenCalled = false;
   int nbrOfCalls = 0;
};

class StepGenTestFixture : public testing::Test 
{
  protected: 
   std::unique_ptr<StepGen> stepGen;
   std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();
   MockStepObserver *mockStepObserver;
   StepObserver2<MockStepObserver, void (&)(MockStepObserver* s)>* stepObserver2;

   void SetUp()
   {
      arduinoStub->Reset();
      stepGen = std::make_unique<StepGen>(test_step_pin, test_dir_pin, t_on_test, t_off_test);
      mockStepObserver = new MockStepObserver;
      stepObserver2 = new StepObserver2<MockStepObserver, void (&)(MockStepObserver* s)>(mockStepObserver, MockStepObserver::UpdateWrapper);
      stepGen->AttachStepObserver(stepObserver2);
   }
   
   void TearDown()
   {
      stepGen.reset();
      //delete stepObserver;
   }
   
   void incTime(unsigned int iterations = 1)
   {
      for (auto i = 0; i < iterations; i++)
      {
         arduinoStub->IncTime(periodicity);
         stepGen->Update();
      }
   }

   bool checkStep(micro_sec t_on, micro_sec t_off, micro_sec period = periodicity)
   {
      bool retVal = true;
      
      for (micro_sec i = 0; i < t_on/periodicity; i++)
      {
         retVal = retVal & (arduinoStub->GetDigitalWrite(test_step_pin) == PinState_High);
         incTime();

         //if (!retVal) cout << "checking step is high at pos " << i << " failed\n";
      }

      for (micro_sec i = 0; i < t_off/periodicity; i++)
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
// output: |"""t_on"""|___t_off___
TEST_F(StepGenTestFixture, test_one_step)
{
   stepGen->Step();
   ASSERT_TRUE(checkStep(t_on_test, t_off_test));
   ASSERT_TRUE(mockStepObserver->hasBeenCalled);
   ASSERT_FALSE(stepGen->IsBusy());
}

// test generating two steps 
// output: |"""t_on"""|___t_off___|"""t_on"""|___t_off___
TEST_F(StepGenTestFixture, test_two_steps)
{
   stepGen->Step(2);
   ASSERT_TRUE(checkStep(t_on_test, t_off_test));
   ASSERT_TRUE(stepGen->IsBusy());
   ASSERT_TRUE(checkStep(t_on_test, t_off_test));
   ASSERT_FALSE(stepGen->IsBusy());
   ASSERT_TRUE(mockStepObserver->nbrOfCalls == 2);
}

// test step returns busy if current step is not done
TEST(StepGenTestGroup, test_busy)
{
   StepGen s(test_step_pin, test_dir_pin, 5000, 5000);

   // precondition, start a step, inc time 4 ms
   ASSERT_TRUE(s.Step() == idle);  
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
   // precondition, start a step
   ASSERT_TRUE(stepGen->Step() == idle);  
   incTime();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_High);

   incTime(2); // increase time += 3*periodicity
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_High);

   incTime();
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_Low);
   ASSERT_TRUE(stepGen->IsBusy()); 

   incTime(4);
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_Low);
   ASSERT_FALSE(stepGen->IsBusy()); 
}

// test generating one step with specified speed
TEST_F(StepGenTestFixture, test_step_with_set_speed)
{
   stepGen->SetStepsPerSec(50);
   stepGen->Step(1); // with 50 steps per sec, one pulse is 20ms
   incTime(1000/periodicity);
   ASSERT_TRUE(stepGen->IsBusy());
   incTime(18000/periodicity);
   ASSERT_TRUE(stepGen->IsBusy());
   incTime(1000/periodicity);
   ASSERT_FALSE(stepGen->IsBusy());
}

// test generating one step with specified speed
// stepGen is set up to have max speed of 500 steps / sec
TEST_F(StepGenTestFixture, test_step_with_to_high_speed)
{
   // given t_on + t_off, highest possibler speed is 500 pps (1/(1ms+1ms)),
   // test speed saturated if above
   stepGen->SetStepsPerSec(600);
   stepGen->Step(1);
   incTime();
   ASSERT_TRUE(stepGen->IsBusy());
   incTime(6);
   ASSERT_TRUE(stepGen->IsBusy());
   incTime(1);
   ASSERT_FALSE(stepGen->IsBusy());
}


TEST_F(StepGenTestFixture, test_decresing_step_length_with_speed_ramp_up)
{
   stepGen->SetUseRamping(true);
   stepGen->SetStepsPerSec(100); // => t_off_steps_per_sec_bias = 8000
 
   constexpr micro_sec t_sps_test = 8000;

   // set nbr of steps >> default_number_of_ramp_steps not to get intervened by ramping down
   stepGen->Step(100); 
   // t_on_test + t_off_test + t_sps_test + t_off_ramp_ - 1 (-1 means "last off-state iteration")
   incTime((t_on_test + t_off_test + t_sps_test + kDefaultMaxTOffRamp - periodicity)/periodicity);

   // still working on the off part of the first step
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_Low);

   incTime(1);
   // new step just started
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_High);

   // first step took 44 ms to finish, 2nd should be done in:
   // t_on_test + t_off_test + t_sps_test + t_off_ramp_ - default_t_delta - 1
   incTime((t_on_test + t_off_test + t_sps_test + kDefaultMaxTOffRamp - 1*default_t_delta - periodicity)/periodicity);
   // all requested steps done
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_Low);
   //ASSERT_FALSE(stepGen->IsBusy());
   incTime(1);
   // new step just started
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_High);

   // 3nd should be done in:
   // t_on_test + t_off_test + t_sps_test + t_off_ramp_ - 2*default_t_delta - 1
   incTime((t_on_test + t_off_test + t_sps_test + kDefaultMaxTOffRamp - 2*default_t_delta - periodicity)/periodicity);
   // all requested steps done
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_Low);
   //ASSERT_FALSE(stepGen->IsBusy());
   incTime(1);
   // new step just started
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_step_pin) == PinState_High);
}

TEST_F(StepGenTestFixture, test_decresing_step)
{
   stepGen->SetUseRamping(true);
   stepGen->SetStepsPerSec(100);
   constexpr micro_sec t_sps_test = 8000;

   constexpr auto ramp_steps = default_number_of_ramp_steps;

   // set nbr of steps >> default_number_of_ramp_steps not to get intervened by ramping down
   stepGen->Step(100); 

   for (int8_t i = 0; i < ramp_steps; i++)
   {
      ASSERT_TRUE(checkStep(t_on_test, t_off_test + t_sps_test + default_t_delta*(ramp_steps-i)));
   }
}

TEST_F(StepGenTestFixture, test_incresing_step_length_with_speed_ramp_down)
{
   stepGen->SetUseRamping(true);
   stepGen->SetStepsPerSec(100);
   
   constexpr micro_sec t_sps_test = 8000;
   constexpr auto ramp_steps = default_number_of_ramp_steps;

   // set nbr of steps to get full ramp up, one steady state step then full ramp down
   stepGen->Step(2 * ramp_steps + 1); 

   // ramping up
   for (int8_t i = 0; i < ramp_steps; i++)
   {
      ASSERT_TRUE(checkStep(t_on_test, t_off_test + t_sps_test + default_t_delta*(ramp_steps-i)));
   }

   // one max speed step
   ASSERT_TRUE(checkStep(t_on_test, t_off_test + t_sps_test));

   // ramping down
   for (int8_t i = 1; i < ramp_steps; i++)
   {
      ASSERT_TRUE(checkStep(t_on_test, t_off_test + t_sps_test + default_t_delta*i));
   }
}

TEST_F(StepGenTestFixture, test_incomlpete_ramping)
{
   stepGen->SetUseRamping(true);
   stepGen->SetStepsPerSec(100);
   
   constexpr micro_sec t_sps_test = 8000;
   constexpr micro_sec ramp_steps = 20; // made up number
   uint16_t requested_steps = 2 * ramp_steps;

   // set nbr of steps to get incomplete ramp up, straight in to incomplete ramp down
   // never reaching full speed
   stepGen->Step(requested_steps);  // hopefully this gives 20 ramp up, 20 ramp down

   // ramping up
   for (int8_t i = 0; i < ramp_steps; i++)
   {
      ASSERT_TRUE(checkStep(t_on_test, t_off_test + t_sps_test + default_t_delta*(default_number_of_ramp_steps-i)));
   }

   // ramping down
   for (int8_t i = 0; i < ramp_steps; i++)
   {
      ASSERT_TRUE(checkStep(t_on_test, t_off_test + t_sps_test + default_t_delta*(default_number_of_ramp_steps - ramp_steps + i + 2)));
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
   StepGen s(test_step_pin, test_dir_pin, 5000, 5000, true);

   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_dir_pin) == HIGH);

   s.SetDirection(direction_reverse);
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_dir_pin) == LOW);
   ASSERT_TRUE(s.GetDirection() == direction_reverse);

   s.SetDirection(direction_forward);
   ASSERT_TRUE(arduinoStub->GetDigitalWrite(test_dir_pin) == HIGH);
   ASSERT_TRUE(s.GetDirection() == direction_forward);
}

TEST_F(StepGenTestFixture, test_step_req_done_observer)
{
   MockStepObserver mockStepObserver;
   MockStepObserver mockDoneObserver;
   StepObserver2<MockStepObserver, void (&)(MockStepObserver* s)>* doneObserver;

   doneObserver = new StepObserver2<MockStepObserver, void (&)(MockStepObserver* s)>(&mockDoneObserver, MockStepObserver::UpdateWrapper);

   stepGen->AttachStepObserver(&mockStepObserver);
   stepGen->AttachDoneObserver(doneObserver);

   stepGen->Step(10); 
   ASSERT_FALSE(mockDoneObserver.hasBeenCalled);
   for (int8_t i = 0; i < 10; i++)
   {
      ASSERT_TRUE(checkStep(t_on_test, t_off_test));
      ASSERT_TRUE(mockStepObserver.nbrOfCalls = i + 1);
   }
   ASSERT_TRUE(mockDoneObserver.hasBeenCalled);
   delete doneObserver;
}

TEST_F(StepGenTestFixture, test_detatch_done_observer)
{

   MockStepObserver mockDoneObserver;
   StepObserver2<MockStepObserver, void (&)(MockStepObserver* s)>* doneObserver;
   doneObserver = new StepObserver2<MockStepObserver, void (&)(MockStepObserver* s)>(&mockDoneObserver, MockStepObserver::UpdateWrapper);
   stepGen->AttachDoneObserver(doneObserver);

   // precond
   // attach doneObserver. make sure it gets called
   stepGen->Step(5); 
   ASSERT_FALSE(mockDoneObserver.hasBeenCalled);
   for (int8_t i = 0; i < 5; i++)
   {
      ASSERT_TRUE(checkStep(t_on_test, t_off_test));
      ASSERT_TRUE(mockStepObserver->nbrOfCalls = i + 1);
   }
   //ASSERT_TRUE(mockDoneObserver.hasBeenCalled);
   mockDoneObserver.Reset();

   // test
   // detach, request steps
   stepGen->DetachDoneObserver();
   stepGen->Step(5); 
   ASSERT_FALSE(mockDoneObserver.hasBeenCalled);
   for (int8_t i = 0; i < 5; i++)
   {
      ASSERT_TRUE(checkStep(t_on_test, t_off_test));
      ASSERT_TRUE(mockStepObserver->nbrOfCalls = i + 1);
   }
   ASSERT_FALSE(mockDoneObserver.hasBeenCalled);
}


}