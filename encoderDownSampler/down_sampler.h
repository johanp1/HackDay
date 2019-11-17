 #ifndef __C_DOWN_SAMPLER_H__
#define __C_DOWN_SAMPLER_H__

#include "Arduino.h"

class DownSampler
{
 public:
  DownSampler(int downSampleRatio);
  ~DownSampler();
  int update(int v);
  void next();
  
 private:
  int stepCount;
  int prev;
  class State *state;
};

class State {
 
 public:
 State(int ratio) : downSamplingRatio(ratio){};
  virtual ~State() {};
  virtual State* next() = 0;
  virtual int getStepsInState() = 0;
  virtual int getOutput() = 0;

  int downSamplingRatio;
};

class Off: public State {
 public:
  Off(int ratio);
  
  State* next();
  int getStepsInState();
  int getOutput();

 private:
  int stepsInState;
};

class On: public State {
 public:
  On(int ratio);

  State* next();
  int getStepsInState();
  int getOutput();
  
 private:
  int stepsInState;
};

#endif // __C_DOWN_SAMPLER_H__
