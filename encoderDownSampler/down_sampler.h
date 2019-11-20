#ifndef __C_DOWN_SAMPLER_H__
#define __C_DOWN_SAMPLER_H__

#include "Arduino.h"

class DownSampler
{
 public:
  DownSampler(int downSampleRatio);
  ~DownSampler();
  int update(int v);
  void setOutput(int v);

 private:
  int stepCount;
  int prev;
  class State *state;
  int output;
};

class State {
 
 public:
  State(int ratio) : downSamplingRatio(ratio){};
  virtual ~State() {};
  virtual State* next(DownSampler* d) = 0;
  virtual int getStepsInState() = 0;

  int downSamplingRatio;
};

class Off: public State {
 public:
  Off(DownSampler* d, int ratio);
  
  State* next(DownSampler* d);
  int getStepsInState();

 private:
  int stepsInState;
};

class On: public State {
 public:
  On(DownSampler* d, int ratio);

  State* next(DownSampler* d);
  int getStepsInState();
  
 private:
  int stepsInState;
};

#endif // __C_DOWN_SAMPLER_H__
