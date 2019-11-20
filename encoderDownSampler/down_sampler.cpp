#include "down_sampler.h"


DownSampler::DownSampler(int downSampleRatio)
{
  prev = 0;

  state = new Off(this, downSampleRatio);
  stepCount = state->getStepsInState()-1; // first pulse will generate state transition
}

DownSampler::~DownSampler()
{
  delete state;
}

int DownSampler::update(int v)
{
  if ((prev == 0) && (v == 1)) 
  {
    stepCount++;
  }

  if (stepCount >= state->getStepsInState()) 
  {
    state = state->next(this);
    
    stepCount = 0;
  }

  prev = v;
  
  return output; 
}

void DownSampler::setOutput(int v)
{
  output = v;
}

Off::Off(DownSampler* d, int ratio) : State(ratio) 
{
  stepsInState = ratio - ratio/2;
    d->setOutput(LOW);
};

State* Off::next(DownSampler* d) 
{
  State *ret = new On(d, downSamplingRatio);
  delete this;
  return ret;
}

int Off::getStepsInState()
{
  return stepsInState;
}

On::On(DownSampler* d, int ratio) : State(ratio) 
{
  stepsInState = ratio/2;
  d->setOutput(HIGH);
};

State* On::next(DownSampler* d) 
{
  State *ret = new Off(d, downSamplingRatio);
  delete this;
  return ret;
}

int On::getStepsInState()
{
  return stepsInState;
}