#include "step_gen.h"
#include <iostream>
//#include <sstream>
#include <Arduino.h>

StepGen::StepGen(Pin step_pin, Pin dir_pin, milli_sec t_on, milli_sec t_off) : t_on_(t_on), t_off_(t_off), step_pin_(step_pin), dir_pin_(dir_pin)
{
   pinMode(step_pin_, OUTPUT);
   pinMode(dir_pin_, OUTPUT);

   use_ramping_ = false;
   max_steps_per_sec_ = 1000 / (t_on_ + t_off_);
   curr_step_ = 0;
   t_off_sps_ = 0;
   t_off_ramp_ = 0;

   SetStepsPerSec(max_steps_per_sec_);
   state_ = new StateInactive(this);
   digitalWrite(step_pin_, state_->GetOutput());
   digitalWrite(dir_pin, LOW);
}

StepGen::~StepGen()
{
   delete state_;
}

void StepGen::Update()
{
   state_->Update();
}

StepRetVal StepGen::Step(unsigned int steps)
{
   if (!IsBusy())
   {
      curr_step_ = steps-1; // current step is the step index [(n-1)..0]

      if (use_ramping_)
      {
         t_off_ramp_ = max_t_off_ramp; // initialize the first ramp step's time offset
         ramp_steps_ = CalcNbrOfRampSteps();
      }
      else
      {
          t_off_ramp_ = 0;
      }

      t_start_ = millis();
      TransitionTo(new StateOn(this));
      return ok;
   }
   else
   {
      return busy;
   }
}

// still busy with generating the step()-request, or ready for new request
bool StepGen::IsBusy()
{
   return state_->IsBusy();
}

void StepGen::SetStepsPerSec(unsigned int steps_per_sec)
{
   if ((steps_per_sec != 0) && (steps_per_sec < max_steps_per_sec_))
   { 
      t_off_sps_ = 1000/steps_per_sec - t_on_ - t_off_;
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
   digitalWrite(dir_pin_, d == direction_forward ? LOW : HIGH);
}

void StepGen::Attach(StepObserver *stepObserver)
{
   stepObserver_ = stepObserver;
}


void StepGen::StartNextStep()
{
   t_start_ = millis();
   curr_step_--;

   if (use_ramping_)
   {
      t_off_ramp_ = CalcRampTimeOffset();
   }
   TransitionTo(new StateOn(this));
}

void StepGen::TransitionTo(State *state) 
{
   if (this->state_ != nullptr)
      delete this->state_;
      
   this->state_ = state;

   digitalWrite(step_pin_, state_->GetOutput());
}

milli_sec StepGen::CalcRampTimeOffset()
{
   milli_sec retVal = t_off_ramp_;

   if (curr_step_ < ramp_steps_)
   {  // ramp down
      t_off_ramp_ <= max_t_off_ramp ? retVal = t_off_ramp_ + t_delta : retVal = max_t_off_ramp;
   }
   else
   {  // ramp up
      t_off_ramp_ > 0 ? retVal = t_off_ramp_ - t_delta : t_off_ramp_ = 0;
   }
   return retVal;
}

unsigned int StepGen::CalcNbrOfRampSteps()
{
   unsigned int retVal;

   // can ramping up and down fit in the number of requested steps?
   if (curr_step_ < 2 * max_number_of_ramp_steps)
   {
      // no, ramp upp as far as possible, will not reach max speed, then ramp down
      retVal = curr_step_ / 2;
   }
   else
   {
      // yes, full ramp-up to max speed, then ramp down when appropriate
      retVal = max_number_of_ramp_steps;
   }

   return retVal;
}

// is the "on"/high part of the full step done
bool StepGen::IsHighDone()
{
   return millis() - t_start_ >= t_on_;
}

// is the "off"/low part of the full step done
bool StepGen::IsLowDone()
{
   return millis() - t_start_ >= t_on_ + t_off_ + t_off_sps_ + t_off_ramp_;
}


void StepGen::UpdateObserver() 
{ 
   if (stepObserver_ != nullptr)
   {
      stepObserver_->Update();
   } 
};

void StateOn::Update()
{
   if (stepGen_->IsHighDone())
   {
      // notify observer that this "step" is done
      stepGen_->UpdateObserver();

      digitalWrite(0, LOW);
      stepGen_->TransitionTo(new StateOff(stepGen_));
   }
}

void StateOff::Update()
{
   if (stepGen_->IsLowDone())
   {
      // start next step, or stop if all steps done
      if (stepGen_->curr_step_ > 0)
      {
         stepGen_->StartNextStep();
      }
      else
      {
         stepGen_->TransitionTo(new StateInactive(stepGen_));
      }
   }   
}


void StateInactive::Update(){}