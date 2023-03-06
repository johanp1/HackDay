#include "step_gen.h"
#include <iostream>

StepGen::StepGen(milli_sec t_on, milli_sec t_off)
{
   pinMode(0, OUTPUT);

   t_on_ = t_on;
   t_off_ = t_off;
   curr_steps_ = 0;
   state_ = new StateInactive(this);
}

StepGen::~StepGen()
{
   delete state_;
}

 stepRetVal StepGen::Step(uint8_t steps)
{
   if (!IsBusy())
   {
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
      // all steps requested done, transition to inactive state
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
}

// is the "on"/high part of the full step done
bool StepGen::IsHighDone()
{
   return millis() - t_start_ >= t_on_;
}

// is the "off"/low part of the full step done
bool StepGen::IsLowDone()
{
   return millis() - t_start_ >= t_on_ + t_off_;
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