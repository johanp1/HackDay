#ifndef __C_STEP_GEN_H__
#define __C_STEP_GEN_H__

using milli_sec = unsigned int;
using Pin = char;

enum StepRetVal { ok, busy };
enum Direction { direction_forward, direction_reverse };

constexpr milli_sec default_t_on = 2; // ms
constexpr milli_sec default_t_off = 3; // ms
constexpr char max_number_of_ramp_steps = 34; // calculated with ocatve-script "calc_n.m"
constexpr milli_sec t_delta = 1;
constexpr milli_sec max_t_off_ramp = max_number_of_ramp_steps * t_delta; 

class State;

class StepGen
{
   public:
   StepGen(Pin stepPin = 0, Pin dirPin = 1, milli_sec t_on = default_t_on, milli_sec t_off = default_t_off);
   virtual ~StepGen();

   virtual void Update();
   virtual StepRetVal Step(unsigned int steps = 1);
   virtual bool IsBusy(); // busy with generating the step()-request
   virtual void SetStepsPerSec(unsigned int steps_per_sec);
   virtual void SetUseRamping(bool use_ramping);
   virtual void SetDirection(Direction d);
   
   private:
   void StartNextStep(); // start one step
   void TransitionTo(State *state);
   milli_sec CalcRampTimeOffset(); // calculate t_off_ramp_
   unsigned int CalcNbrOfRampSteps(); // calculate how many ramping up/down steps we can squeez in
   bool IsHighDone();  // is the "on" part of the step done
   bool IsLowDone();  // is the "off" part of the step done

   milli_sec t_on_; // the step's "on-time" length
   milli_sec t_off_; // the step's "off-time"
   unsigned int max_steps_per_sec_;
   milli_sec t_off_sps_; // the step's "off-time" offset when using setting "Steps Per Sec"
   milli_sec t_off_ramp_; // the step's "off-time" offset when ramping speed
   milli_sec t_start_; // start time of current step
   unsigned int curr_step_; // number of steps left untill done with step request
   unsigned int ramp_steps_;
   bool use_ramping_;

   State *state_;
   Pin step_pin_;
   Pin dir_pin_;

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
   virtual char GetOutput() = 0;
};

class StateOn : public State 
{
   public:
   StateOn(StepGen *stepGen) : State(stepGen){};
   bool IsBusy() override {return true;};
   void Update() override;
   char GetOutput() override {return 1;};
};

class StateOff : public State 
{
   public:
   StateOff(StepGen *stepGen) : State(stepGen){};
   bool IsBusy() override {return true;};
   void Update() override;
   char GetOutput() override {return 0;};
};

class StateInactive : public State 
{
   public:   
   StateInactive(StepGen *stepGen) : State(stepGen){};
   void Update() override;
   char GetOutput() override {return 0;};
};


#endif