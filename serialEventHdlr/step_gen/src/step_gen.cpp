#include "step_gen.h"
//#include <iostream>
//#include <sstream>

StepGen::StepGen(Pin pin, milli_sec t_on, milli_sec t_off) : t_on_(t_on), t_off_(t_off), pin_(pin)
{
   pinMode(pin, OUTPUT);

   use_ramping_ = false;
   max_steps_per_sec_ = 1000 / (t_on_ + t_off_);
   curr_steps_ = 0;

   SetStepsPerSec(max_steps_per_sec_);
   state_ = new StateInactive(this);
   digitalWrite(pin_, state_->GetOutput());
}

StepGen::~StepGen()
{
   delete state_;
}

stepRetVal StepGen::Step(uint16_t steps)
{
   if (!IsBusy())
   {
      if (use_ramping_)
      {
         // set t_off_ramp_ = t_delta*(n+1), will get decresed to n before 
         // step is started in StartStep
         t_off_ramp_ = init_t_off_ramp + t_delta;

         // can ramping up and down fit in the number of requested steps?
         if (steps < 2 * default_number_of_ramp_steps)
         {
            // no, ramp upp as far as possible, will not reach max speed, then ramp down
            ramp_steps_ = steps / 2;
         }
         else
         {
            // yes, full ramp-up to max speed, then ramp down when appropriate
            ramp_steps_ = default_number_of_ramp_steps;
         }
      }
      else
      {
          t_off_ramp_ = 0;
      }

      curr_steps_ = steps;
      StartStep();
      return ok;
   }
   else
   {
      return busy;
   }
}

void StepGen::StartStep()
{
   if (curr_steps_ > 0)
   {
      t_start_ = millis();
      curr_steps_--;
      
      if (use_ramping_)
      {
         t_off_ramp_ = CalcRampTimeOffset();
      }
      TransitionTo(new StateOn(this));
      //cout << "starting step " << to_string(curr_steps_) << ", t_on " << t_on_ << ", t_off " << t_off_ + t_off_ramp_ << "\n";
   }
   else
   {
      // all steps requested are done, transition to inactive state
      TransitionTo(new StateInactive(this));
   }
}

void StepGen::Update()
{
   state_->Update();
}

void StepGen::TransitionTo(State *state) 
{
   if (this->state_ != nullptr)
      delete this->state_;
      
   this->state_ = state;

   digitalWrite(pin_, state_->GetOutput());
}

milli_sec StepGen::CalcRampTimeOffset()
{
   milli_sec retVal = t_off_ramp_;

   if (curr_steps_ < ramp_steps_)
   {  // ramp down
      t_off_ramp_ <= init_t_off_ramp ? retVal = t_off_ramp_ + t_delta : retVal = init_t_off_ramp;
   }
   else
   {  // ramp up
      t_off_ramp_ > 0 ? retVal = t_off_ramp_ - t_delta : t_off_ramp_ = 0;
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

// still busy with generating the step()-request, or ready for new request
bool StepGen::IsBusy()
{
   return state_->IsBusy();
}

void StepGen::SetStepsPerSec(uint8_t steps_per_sec)
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

void StateOn::Update()
{
   if (stepGen_->IsHighDone())
   {
      digitalWrite(0, LOW);
      stepGen_->TransitionTo(new StateOff(stepGen_));
   }
}

void StateOff::Update()
{
   if (stepGen_->IsLowDone())
   {
      // start next step, or stop if all steps done
      stepGen_->StartStep();
   }
}


void StateInactive::Update(){}