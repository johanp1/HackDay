#ifndef __C_LCD_WRITER_H__
#define __C_LCD_WRITER_H__

#include <Arduino.h>

using milli_sec = uint16_t;
using Pin = byte;

enum stepRetVal { ok, busy };

constexpr milli_sec default_t_on = 5; //5ms
constexpr milli_sec default_t_off = 5; //5ms

class State;

class StepGen
{
   public:
   StepGen(Pin pin = 0, milli_sec t_on = default_t_on, milli_sec t_off = default_t_off);
   virtual ~StepGen();

   virtual void Update();
   virtual stepRetVal Step(uint16_t steps = 1, uint16_t steps_per_sec = 0);
   bool IsBusy(); // busy with generating the step()-request

   private:
   void StartStep(); // start one step
   void TransitionTo(State *state);

   bool IsHighDone();  // is the "on" part of the step done
   bool IsLowDone();  // is the "off" part of the step done

   milli_sec t_on_; // the step's "on" length
   milli_sec t_off_; // the step's "off" length
   uint16_t max_steps_per_sec_;
   milli_sec t_off_speed_; // the step's "off" length offset when using "set speed"
   milli_sec t_start_; // start time of current step
   uint16_t curr_steps_; // number of steps left untill done with step()
   State *state_;
   Pin pin_;

   // Friendship is not inherited to children of State. All freindships need to be explicit...
   friend class StateOn;
   friend class StateOff;
   friend class StateInactive;
};

// virtual state base class
class State 
{
   protected:
   StepGen *stepGen_;

   public:
   State(StepGen *stepGen) : stepGen_(stepGen){};
   virtual ~State(){};

   virtual bool IsBusy() {return false;};
   virtual void Update() = 0;
   virtual byte GetOutput() = 0;
};

class StateOn : public State 
{
   public:
   StateOn(StepGen *stepGen) : State(stepGen){};
   bool IsBusy() override {return true;};
   void Update() override;
   byte GetOutput() override {return HIGH;};
};

class StateOff : public State 
{
   public:
   StateOff(StepGen *stepGen) : State(stepGen){};
   bool IsBusy() override {return true;};
   void Update() override;
   byte GetOutput() override {return LOW;};
};

class StateInactive : public State 
{
   public:   
   StateInactive(StepGen *stepGen) : State(stepGen){};
   void Update() override;
   byte GetOutput() override {return LOW;};
};


#endif