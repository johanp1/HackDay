#include "step_gen.h"
//#include <iostream>
//#include <sstream>
#include <Arduino.h>

constexpr unsigned long kMicroSecundsPerSec = 1000000;

StepGen::StepGen(Pin step_pin, Pin dir_pin, micro_sec t_on, micro_sec t_off, bool flip, micro_sec t_d, unsigned int number_of_ramp_steps) : t_on_(t_on), t_off_(t_off), step_pin_(step_pin), dir_pin_(dir_pin), flipped_(flip), t_delta_(t_d), number_of_ramp_steps_(number_of_ramp_steps)
{
   pinMode(step_pin_, OUTPUT);
   pinMode(dir_pin_, OUTPUT);

   use_ramping_ = false;
   max_steps_per_sec_ = 1000000 / (t_on_ + t_off_);
   curr_step_ = 0;
   t_off_sps_ = 0;
   t_off_ramp_ = 0;

   SetStepsPerSec(max_steps_per_sec_);
   SetState(state_inactive);
   SetDirection(direction_forward);
}

StepGen::~StepGen()
{
}

void StepGen::Update()
{
   if (state_ == state_on)
   {
      if (IsHighDone())
      {      
         SetState(state_off);
      }
   }
   else if (state_ == state_off)
   {
      if (IsLowDone())
      {
         // notify observer that this "step" is done
         UpdateStepObserver();

         // start next step, or stop if all steps done
         if (curr_step_ > 0)
         {
            StartNextStep();
         }
         else
         {
            SetState(state_inactive);

            UpdateDoneObserver();
         }
      }  
   }
   else{}
}

StepRetVal StepGen::Step(unsigned int steps)
{
   if (!IsBusy())
   {
      curr_step_ = steps - 1; // current step is the step index [(n-1)..0]

      if (use_ramping_)
      {
         t_off_ramp_ = number_of_ramp_steps_ * t_delta_; // initialize the first ramp step's time offset
         ramp_steps_ = CalcNbrOfRampSteps(steps);
      }
      else
      {
          t_off_ramp_ = 0;
      }

      //t_start_ = millis();
      t_start_ = micros();
      SetState(state_on);
      return idle;
   }
   else
   {
      return busy;
   }
}

// still busy with generating the step()-request, or ready for new request
bool StepGen::IsBusy()
{
   return (state_ == state_on) || (state_ == state_off);
}

void StepGen::SetStepsPerSec(unsigned int steps_per_sec)
{
   if ((steps_per_sec != 0) && (steps_per_sec < max_steps_per_sec_))
   { 
      t_off_sps_ = 1000000/steps_per_sec - t_on_ - t_off_;
   }
   else
   {
      t_off_sps_ = 0;
   }
}

void StepGen::SetUseRamping(bool use_ramping)
{
   use_ramping_ = use_ramping;
}

void StepGen::SetDirection(Direction d)
{
   digitalWrite(dir_pin_, (d == direction_forward) ^ (flipped_ == true) ? LOW : HIGH);
}

Direction StepGen::GetDirection()
{
   return ((digitalRead(dir_pin_) == LOW ) ^ (flipped_ == true) ? direction_forward : direction_reverse);
}

void StepGen::AttachStepObserver(StepObserver *o)
{
   stepObserver_ = o;
}

void StepGen::AttachDoneObserver(StepObserver *o)
{
   doneObserver_ = o;
}

void StepGen::DetachDoneObserver()
{
   doneObserver_ = nullptr;
}

void StepGen::StartNextStep()
{
   t_start_ = micros();
   curr_step_--;

   if (use_ramping_)
   {
      t_off_ramp_ = CalcRampTimeOffset();
   }

   SetState(state_on);
}

micro_sec StepGen::CalcRampTimeOffset()
{
   micro_sec retVal = t_off_ramp_;
   unsigned long max_t_off_ramp = number_of_ramp_steps_ * t_delta_;

   if (curr_step_ < ramp_steps_)
   {  // ramp down
      t_off_ramp_ <= max_t_off_ramp ? retVal = t_off_ramp_ + t_delta_ : retVal = max_t_off_ramp;
   }
   else
   {  // ramp up
      t_off_ramp_ > 0 ? retVal = t_off_ramp_ - t_delta_ : t_off_ramp_ = 0;
   }

   return retVal;
}

unsigned int StepGen::CalcNbrOfRampSteps(unsigned int steps)
{
   unsigned int retVal;

   // can ramping up and down fit in the number of requested steps?
   if (steps < 2 * number_of_ramp_steps_)
   {
      // no, ramp upp as far as possible, will not reach max speed, then ramp down
      retVal = steps / 2;
   }
   else
   {
      // yes, full ramp-up to max speed, then ramp down when appropriate
      retVal = number_of_ramp_steps_;
   }

   return retVal;
}

// is the "on"/high part of the full step done
bool StepGen::IsHighDone()
{
   //return millis() - t_start_ >= t_on_;
   return micros() - t_start_ >= t_on_;
}

// is the "off"/low part of the full step done
bool StepGen::IsLowDone()
{
   //return millis() - t_start_ >= t_on_ + t_off_ + t_off_sps_ + t_off_ramp_;
   unsigned long current_time = micros();
   return current_time - t_start_ >= t_on_ + t_off_ + t_off_sps_ + t_off_ramp_;
}

void StepGen::UpdateStepObserver() 
{ 
   if (stepObserver_ != nullptr)
   {
      (*stepObserver_)();
   } 
};

void StepGen::UpdateDoneObserver() 
{ 
   if (doneObserver_ != nullptr)
   {
      (*doneObserver_)();
   } 
};

void StepGen::SetState(State s)
{
   state_ = s;
   digitalWrite(step_pin_, state_ == state_on ? HIGH : LOW);
}