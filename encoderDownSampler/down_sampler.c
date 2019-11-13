#include "down_sampler.h"

//the STEPS_PER_STATE needs to be an integer
#define DOWN_SAMPLING_RATIO 4  // we have 500 steps/rev, down sampled with 4 gives output of 125 steps/rev
#define STEPS_PER_STATE DOWN_SAMPLING_RATIO/2

DownSampler::DownSampler(int downSampleRatio)
	{
		stepCount = 0;
		prev   = 0;
		state = LOW;
      state = StateContainer(downSampleRatio);
	};
	
int DownSampler::update(int v)
{
   if ((prev == LOW) && (v == HIGH))
	{
		stepCount++;
		prev = v;
	}
		
	if (stepCount >= state.getStepsInState())
	{
		// toggle state
		state.next();
    
		stepCount = 0;
	}
		
	return state.currState();
}
