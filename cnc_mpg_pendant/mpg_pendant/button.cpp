#include "button.h"
 
//   public:

// constructor 
C_Button::C_Button(const String& argName, const int argPin, const long argDebounceDelay) : C_EventGenerator(argName), pin(argPin), debounceTime(argDebounceDelay)
{
   prevState = LOW;
   time = 0;
   pinMode(pin, INPUT);
}


// returns debounced button state
void C_Button::scan(void)
{
   int currState = digitalRead(pin); // read pin

   if (currState != prevState)
   {
      //Serial.print("new state?");
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


