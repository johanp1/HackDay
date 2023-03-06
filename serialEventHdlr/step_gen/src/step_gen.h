#ifndef __C_LCD_WRITER_H__
#define __C_LCD_WRITER_H__

#include <Arduino.h>

using milli_sec = uint16_t;

constexpr milli_sec default_t_on = 5; //5ms
constexpr milli_sec default_t_off = 5; //5ms

class StepGen;

// virtual state base class
class State 
{
   protected:
   StepGen *stepGen_;

   public:
   State(StepGen *stepGen) : stepGen_(stepGen){};
   virtual ~State(){};
   virtual void Update() = 0;
};

class StateOn : public State 
{
   public:
   StateOn(StepGen *stepGen) : State(stepGen){}; 
   void Update() override;
};

class StateOff : public State 
{
   public:
   StateOff(StepGen *stepGen) : State(stepGen){};
   void Update() override;
};

class StateInactive : public State 
{
   public:   
   StateInactive(StepGen *stepGen) : State(stepGen){};
   void Update() override;
};

class StepGen
{
   public:
   StepGen(milli_sec t_on = default_t_on, milli_sec t_off = default_t_off);
   virtual ~StepGen();

   virtual void Update();
   virtual void Step(uint8_t steps = 1);
   void TransitionTo(State *state);

   bool IsHighStepDone();
   bool IsLowStepDone();
   bool IsDone();

   private:
   milli_sec t_on_;
   milli_sec t_off_;
   milli_sec t_start_;
   uint8_t curr_state_;
   uint16_t curr_steps_;

   State *state_;
};

#endif