#include "selector.h"

#define LIMIT 60u


//   public:

// constructor 
Selector::Selector(const String& argName,
		       const unsigned int argPin,
		       const unsigned long argDebounceDelay) : EventGenerator(argName), pin(argPin), debounceTime(argDebounceDelay)
{
  state = 0;
  prevState = state;
  time = 0;
}

Selector::Selector(const String& argName,
		       const unsigned int argPin,
		       const unsigned long argDebounceDelay,
             const unsigned int stateVolts[numberOfStates_]) : EventGenerator(argName), pin(argPin), debounceTime(argDebounceDelay)
{
  state = 0;
  prevState = state;
  time = 0;

  // copy new values
  for (byte i = 0; i < numberOfStates_; i++)
  {
     stateVals_[i] = stateVolts[i];
  }
}

// returns debounced selector state
void Selector::scan(void)
{
  byte currState = volt2state((unsigned int)analogRead((int)pin)); // read pin
  if (currState != prevState)
  {
    // reset the debouncing timer
    time = millis();
  }
  
  if ((millis() - time) > debounceTime) {
  // take the new reading since debounce timer elapsed
    if (currState != state) 
    {
      state = currState;
      generateEvent(state);
    }
  }
      
  prevState = currState;
}

byte Selector::getState()
{
  return state;
}

byte Selector::volt2state(unsigned int volt)
{
   byte i = 0;
   byte retVal = 0;
   bool found = 0;   
   
   while((i < numberOfStates_) && !found)
   {
      if( (stateVals_[i]-LIMIT < volt) && (volt < stateVals_[i]+LIMIT) )
      {
         found = 1;
         retVal = i;
      }
      
      i++;
   }

   return retVal;
}
