 #ifndef __C_DOWN_SAMPLER_H__
#define __C_DOWN_SAMPLER_H__

class DownSampler
{
   public:
	DownSampler(int downSampleRatio);
	int update(int v);
	
	private:
	int state;
	int stepCount;
	int prev;
   StateContainer state;
}

class StateContainer
{
   public:
   StateContainer(int downSampleRatio)
   {
      currState = LOW;
      stepsInState[0] = 2;
      stepsInState[0] = 2;
   };
   
   int currState()
   {
      return LOW;
   };
   
   void next();
   {};
   
   int getStepsInState()
   {
      return 2;
   };
   
   private:
   int stepsInState[2];
   int currState;
}

#endif // __C_DOWN_SAMPLER_H__