#include "button.h"
 
//   public:

// constructor 
Button::Button(const String& argName, const int argPin, const unsigned long argDebounceDelay) : EventGenerator(argName), pin(argPin), debounceTime(argDebounceDelay)
{
  state = LOW;
  prevState = state;
  time = 0;
  pinMode(pin, INPUT);
}

// returns debounced button state
void Button::scan(void)
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

unsigned int Button::getState()
{
  return state;
}
