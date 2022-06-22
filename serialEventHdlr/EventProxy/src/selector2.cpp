#include "selector2.h"

#define LIMIT 60u
#define NUM_STATES 4

//   public:

// constructor 
Selector2::Selector2(const String& argName,
		       const unsigned int argPin1,
             const unsigned int argPin2,
             const unsigned int argPin3,
		       const unsigned long argDebounceDelay) : EventGenerator(argName), 
                                                     pin1(argPin1),
                                                     pin2(argPin2),
                                                     pin3(argPin3),
                                                     debounceTime(argDebounceDelay)
{
  pinMode(pin1, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);
  pinMode(pin3, INPUT_PULLUP);
  state = 0;
  prevState = state;
  time = 0;
}

// returns debounced selector state
void Selector2::scan(void)
{
  byte currState = 0;
  currState = digitalRead(pin1) == LOW ? 1 : 0;
  currState |= digitalRead(pin2) == LOW ? 2 : 0;
  currState |= digitalRead(pin3) == LOW ? 3 : 0;
  
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