 #ifndef __C_DOWN_SAMPLER_H__
#define __C_DOWN_SAMPLER_H__

#include "Arduino.h"

class StateContainer
{
   public:
   StateContainer(int downSampleRatio);
   
   int getCurrState();
   void next();   
   int getStepsInState();

   private:
   int stepsInState[2];
   int currState;
   const int nbrOfStates;
};



class DownSampler
{
 public:
  DownSampler(int downSampleRatio);
  int update(int v);
	
 private:
  int stepCount;
  int prev;
  StateContainer state;
};

#endif // __C_DOWN_SAMPLER_H__
