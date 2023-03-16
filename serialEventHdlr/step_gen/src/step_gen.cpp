#include "step_gen.h"
//#include <iostream>

StepGen::StepGen(Pin pin, milli_sec t_on, milli_sec t_off) : t_on_(t_on), t_off_(t_off), pin_(pin)
{
   pinMode(pin, OUTPUT);

   curr_steps_ = 0;
   max_steps_per_sec_ = 1000 / (t_on_ + t_off_);
   t_off_speed_ = 0;
   state_ = new StateInactive(this);
   digitalWrite(pin_, state_->GetOutput());
}

StepGen::~StepGen()
{
   delete state_;
}

 stepRetVal StepGen::Step(uint16_t steps, uint16_t steps_per_sec)
{
   if (!IsBusy())
   {
      // if use_speed_ramp_up is used:
      // set t_off_accel_ = n+1, will get decresed to n before 
      // step is started in StartStep
      //use_speed_ramp_up ? t_off_accel_ = 30+1 : t_off_accel_ = 0;

      if ((steps_per_sec != 0) && (steps_per_sec < max_steps_per_sec_))
      { 
         t_off_speed_ = 1000/steps_per_sec - t_on_ - t_off_;
      }
      else
      {
         t_off_speed_ = 0; // use max speed
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

      TransitionTo(new StateOn(this));
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

// is the "on"/high part of the full step done
bool StepGen::IsHighDone()
{
   return millis() - t_start_ >= t_on_;
}

// is the "off"/low part of the full step done
bool StepGen::IsLowDone()
{
   return millis() - t_start_ >= t_on_ + t_off_ + t_off_speed_;
}

// still busy with generating the step()-request, or ready for new request
bool StepGen::IsBusy()
{
   return state_->IsBusy();
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