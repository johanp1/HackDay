#include "button.h"
 
//   public:

// constructor 
Button::Button(const String& argName, const int argPin, const unsigned long argDebounceDelay, const bool flipped) : EventGenerator(argName), pin(argPin), debounceTime(argDebounceDelay), flipped_{flipped}
{
  state = readCurrentState();
  prevState = state;
  time = 0;

  pinMode(pin, INPUT);
}

// returns debounced button state
void Button::scan(void)
{
   ButtonState currState = readCurrentState();

   if (currState != prevState)
   {
      time = millis();   // reset the debouncing timer
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

ButtonState Button::getState()
{
  return state;
}

ButtonState Button::readCurrentState()
{
   // xor
   if (!(digitalRead(pin) == HIGH) != !flipped_) {
      return BUTTON_PRESSED;
   }
   return BUTTON_RELEASED;
}

ButtonState ButtonPullup::readCurrentState() 
{
   return Button::readCurrentState() == BUTTON_PRESSED ? BUTTON_RELEASED : BUTTON_PRESSED;
}
