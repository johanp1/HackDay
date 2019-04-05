 #ifndef __C_BUTTON_H__
#define __C_BUTTON_H__

#include <Arduino.h>
#include "event_generator.h"

class C_Button : public C_EventGenerator {
 
   public:

    // constructor 
   C_Button(const String& argName, const int argPin, const long argDebounceDelay);
  
   void scan(void);

   private:
 
   int pin;
   int state; // debounced buttons tate
   int prevState; // previuos read button state
   unsigned long debounceTime;
   unsigned long time;
};

#endif // __BUTTON_H__

