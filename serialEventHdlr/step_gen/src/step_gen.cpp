#include "step_gen.h"
#include <iostream>

enum State2 { inactive, busy_on, busy_off };

StepGen::StepGen(milli_sec t_on, milli_sec t_off)
{
   pinMode(0, OUTPUT);

   t_on_ = t_on;
   t_off_ = t_off;
   curr_state_ = inactive;
   curr_steps_ = 0;
   state_ = new StateInactive(this);
}

StepGen::~StepGen()
{
   delete state_;
}

void StepGen::Step(uint8_t steps)
{
   digitalWrite(0, HIGH);
   t_start_ = millis();
   curr_steps_ = steps;

   TransitionTo(new StateOn(this));
   curr_state_ = busy_on;
}

void StepGen::Update()
{
   unsigned long ms = millis();

   state_->Update();

   if (curr_state_ == busy_on)
   {
      if (ms - t_start_ >= t_on_)
      {
         // toggle output
         digitalWrite(0, LOW);
         curr_state_ = busy_off;
      }
   }

   if (curr_state_ == busy_off)
   {
      if (ms - t_start_ >= t_on_ + t_off_)
      {
         curr_state_ = inactive;
         digitalWrite(0, LOW);

         if (curr_steps_ > 0)
         {
            curr_steps_--;
            t_start_ = ms;
            curr_state_ = busy_on;
            digitalWrite(0, HIGH);
         }
      }
   }
}

void StepGen::TransitionTo(State *state) 
{
   if (this->state_ != nullptr)
      delete this->state_;
      
   this->state_ = state;
}

bool StepGen::IsHighStepDone()
{
   return millis() - t_start_ >= t_on_;
}

bool StepGen::IsLowStepDone()
{
   return millis() - t_start_ >= t_on_ + t_off_;
}

bool StepGen::IsDone()
{
   return curr_steps_ > 0;
}

void StateOn::Update()
{
   if (stepGen_->IsHighStepDone())
   {
      // toggle output
      digitalWrite(0, LOW);
      stepGen_->TransitionTo(new StateOff(stepGen_));
   }
}

void StateOff::Update()
{
   if (stepGen_->IsLowStepDone())
   {
      stepGen_->IsDone() ? stepGen_->TransitionTo(new StateInactive(stepGen_)) : stepGen_->TransitionTo(new StateOn(stepGen_));
   }
}

void StateInactive::Update(){}