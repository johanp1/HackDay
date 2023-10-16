#ifndef __C_STEP_GEN_H__
#define __C_STEP_GEN_H__

using micro_sec = unsigned int;
using Pin = char;

enum State { state_on, state_off, state_inactive };
enum StepRetVal { idle, busy };
enum Direction { direction_forward, direction_reverse };
 
constexpr micro_sec default_t_on = 2000; //micro secunds (us)
constexpr micro_sec default_t_off = 3000; // us
constexpr micro_sec default_t_delta = 1000; // us, used for ramp-steps
constexpr unsigned int default_number_of_ramp_steps = 43; // calculated with ocatve-script "calc_n.m"
//constexpr unsigned long max_t_off_ramp = default_number_of_ramp_steps * default_t_delta; 

class StepObserver
{
   public:
   virtual void Update() = 0;
};

class StepGen
{
   public:
   StepGen(Pin stepPin = 0, Pin dirPin = 1, micro_sec t_on = default_t_on, micro_sec t_off = default_t_off, bool flip = false, micro_sec t_d = default_t_delta, unsigned int number_of_ramp_steps = default_number_of_ramp_steps);
   virtual ~StepGen();

   virtual void Update();
   virtual StepRetVal Step(unsigned int steps = 1);
   virtual bool IsBusy(); // busy with generating the step()-request
   virtual void SetStepsPerSec(unsigned int steps_per_sec);
   virtual void SetUseRamping(bool use_ramping);
   virtual void SetDirection(Direction d);
   virtual Direction GetDirection();
   void Attach(StepObserver *stepObserver);
   
   private:
   void StartNextStep(); // start one step
   void TransitionTo(State *state);
   micro_sec CalcRampTimeOffset(); // calculate t_off_ramp_
   unsigned int CalcNbrOfRampSteps(unsigned int steps); // calculate how many ramping up/down steps we can squeez in
   bool IsHighDone();  // is the "on" part of the step done
   bool IsLowDone();  // is the "off" part of the step done
   void UpdateObserver();
   void SetState(State s);

   micro_sec t_on_; // the step's "on-time" length
   micro_sec t_off_; // the step's "off-time"
   unsigned  max_steps_per_sec_;
   micro_sec t_off_sps_; // the step's "off-time" offset when using setting "Steps Per Sec"
   unsigned long t_off_ramp_; // the step's "off-time" offset when ramping speed
   unsigned long t_start_; // start time of current step
   unsigned int curr_step_; // number of steps left untill done with step request
   unsigned int ramp_steps_;
   bool use_ramping_;
   bool flipped_;
   unsigned int number_of_ramp_steps_;
   micro_sec t_delta_;

   StepObserver *stepObserver_ = nullptr;
   State state_;
   Pin step_pin_;
   Pin dir_pin_;
};

#endif