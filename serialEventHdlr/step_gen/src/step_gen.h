#ifndef __C_LCD_WRITER_H__
#define __C_LCD_WRITER_H__

#include <Arduino.h>

using milli_sec = uint16_t;
enum stepRetVal { ok, busy };

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

   virtual bool IsBusy() {return false;};
   virtual void Update() = 0;
};

class StateOn : public State 
{
   public:
   StateOn(StepGen *stepGen) : State(stepGen){digitalWrite(0, HIGH);};
   bool IsBusy() override {return true;};
   void Update() override;
};

class StateOff : public State 
{
   public:
   StateOff(StepGen *stepGen) : State(stepGen){digitalWrite(0, LOW);};
   bool IsBusy() override {return true;};
   void Update() override;
};

class StateInactive : public State 
{
   public:   
   StateInactive(StepGen *stepGen) : State(stepGen){digitalWrite(0, LOW);};
   void Update() override;
};

class StepGen
{
   public:
   StepGen(milli_sec t_on = default_t_on, milli_sec t_off = default_t_off);
   virtual ~StepGen();

   virtual void Update();
   virtual stepRetVal Step(uint8_t steps = 1);
   bool IsBusy(); // busy with generating the step()-request

   private:
   void StartStep(); // start one step
   void TransitionTo(State *state);

   bool IsHighDone();  // is the "on" part of the step done
   bool IsLowDone();  // is the "off" part of the step done

   milli_sec t_on_; // the step's "on" length
   milli_sec t_off_; // the step's "off" length
   milli_sec t_start_; // start time of current step
   uint16_t curr_steps_; // number of steps left untill done with step()
   State *state_;

   // Friendship is not inherited to children of State. All freindships need to be explicit...
   friend class StateOn;
   friend class StateOff;
   friend class StateInactive;
};

#endif