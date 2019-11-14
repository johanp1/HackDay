#include "down_sampler.h"
#include <iostream>

//the STEPS_PER_STATE needs to be an integer
//#define DOWN_SAMPLING_RATIO 4  // we have 500 steps/rev, down sampled with 4 gives output of 125 steps/rev
//#define STEPS_PER_STATE DOWN_SAMPLING_RATIO/2

StateContainer::StateContainer(int downSampleRatio) : nbrOfStates(2)
{
  currState = 0;

  // if downSampleRatio nod even number, let state 0 last one sample more 
  stepsInState[1] = downSampleRatio/2;
  stepsInState[0] = downSampleRatio - stepsInState[1];
}
   
int StateContainer::getCurrState()
{
  return currState;
}

void StateContainer::next()
{
  currState = (currState == 0 ? 1 : 0);
}

int StateContainer::getStepsInState()
{
  return stepsInState[currState];
}


DownSampler::DownSampler(int downSampleRatio) : state(downSampleRatio)
{
  stepCount = 0;
  prev = 0;
};
	
int DownSampler::update(int v)
{
  if ((prev == 0) && (v == 1)) {
    stepCount++;
  }
  
  if (stepCount >= state.getStepsInState()) {
    state.next();

    stepCount = 0;
  }

  prev = v;
  
  return state.getCurrState();
}
