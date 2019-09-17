#include "button.h"
 
//   public:

// constructor 
C_Button::C_Button(const String& argName, const int argPin, const unsigned long argDebounceDelay) : C_EventGenerator(argName), pin(argPin), debounceTime(argDebounceDelay)
{
  state = LOW;
  prevState = state;
  time = 0;
  pinMode(pin, INPUT);
}


// returns debounced button state
void C_Button::scan(void)
{
   unsigned int currState = (unsigned int)digitalRead(pin); // read pin

   if (currState != prevState)
   {
      //Serial.print("new state?");
      // reset the debouncing timer
      time = millis();
   }

   if ((millis() - time) >= debounceTime) {
      // take the new reading since debounce timer elapsed
      if (currState != state) 
      {
         state = currState;
         generateEvent(state);
      }
   }
      
   prevState = currState;
}

unsigned int C_Button::getState()
{
  return state;
}
