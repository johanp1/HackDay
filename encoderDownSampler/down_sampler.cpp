#include "down_sampler.h"


DownSampler::DownSampler(int downSampleRatio)
{
  prev = 0;

  state = new Off(downSampleRatio);
  stepCount = state->getStepsInState()-1; // first pulse will generate state transition
}

DownSampler::~DownSampler()
{
  delete state;
}

int DownSampler::update(int v)
{
  if ((prev == 0) && (v == 1)) {
    stepCount++;
  }

  if (stepCount >= state->getStepsInState()) {
    state = state->next();
    
    stepCount = 0;
  }

  prev = v;
  
  return state->getOutput();
}

Off::Off(int ratio) : State(ratio) {
  stepsInState = ratio - ratio/2;
};

State* Off::next() {
  State *ret = new On(downSamplingRatio);
  delete this;
  return ret;
}

int Off::getStepsInState()
{
  return stepsInState;
}

int Off::getOutput()
{
  return LOW;
}

On::On(int ratio) : State(ratio) {
  stepsInState = ratio/2;
};

State* On::next() {
  State *ret = new Off(downSamplingRatio);
  delete this;
  return ret;
}

int On::getStepsInState()
{
  return stepsInState;
}

int On::getOutput()
{
  return HIGH;
}
