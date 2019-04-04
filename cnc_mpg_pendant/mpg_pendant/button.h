 #ifndef __C_BUTTON_H__
#define __C_BUTTON_H__
#include "event_generator.h"

class C_Button : public C_EventGenerator {
 
   public:

    // constructor 
   C_Button(C_Buffer* b, const String& argName, const int argPin, const long argDebounceDelay) : C_EventGenerator(b), name(argName), pin(argPin), debounceTime(argDebounceDelay)
   {
      prevState = LOW;
      time = 0;
      pinMode(pin, INPUT);
   };


   // returns debounced button state
   void scan(void)
   {
      int currState = digitalRead(pin); // read pin
      //Serial.print("curr_state: ");
      //Serial.println(currState);
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
            generateEvent(C_Event(name, state));
         }
      }
      
      prevState = currState;
   };


   private:
 
   int pin;
   int state; // debounced buttons tate
   int prevState; // previuos read button state
   unsigned long debounceTime;
   unsigned long time;
   String name;
};

#endif // __BUTTON_H__

