 #ifndef __C_SELECTOR_H__
#define __C_SELECTOR_H__

#include <Arduino.h>
#include "event_generator.h"

class C_Selector : public C_EventGenerator {
 
   public:

    // constructor 
   C_Selector(const String& argName, const int argPin, const long argDebounceDelay);
  
   void scan(void);
   byte volt2state(int volt);
   private:
 
   int pin;
   int state; // debounced state
   int prevState; // previuos read state
   unsigned long debounceTime;
   unsigned long time;
};

#endif // __C_SELECTOR_H__
