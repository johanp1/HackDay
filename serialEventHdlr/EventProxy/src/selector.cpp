#include "selector.h"

//   public:
Selector::Selector(const String& argName,
		       const unsigned int argPin,
		       const unsigned long argDebounceDelay,
             const unsigned int stateVolts[],
             const byte numberOfStates,
             const byte stateValueUncertainty) : EventGenerator(argName), pin(argPin), debounceTime(argDebounceDelay), stateValueUncertainty_(stateValueUncertainty)
{
   state = 255;
   prevState = state;
   time = 0;

   states_.numberOfStates = numberOfStates;
   states_.stateADValues = new int[numberOfStates];

   // copy new values
   for (byte i = 0; i < states_.numberOfStates; i++)
   {
      states_.stateADValues[i]  = stateVolts[i];
   }
}

Selector::~Selector()
{
   delete states_.stateADValues;
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
   
   while((i < states_.numberOfStates) && !found)
   {
      if( (states_.stateADValues[i]-stateValueUncertainty_ < volt) && (volt < states_.stateADValues[i]+stateValueUncertainty_) )
      {
         found = 1;
         retVal = i;
      }
      
      i++;
   }

   return retVal;
}
