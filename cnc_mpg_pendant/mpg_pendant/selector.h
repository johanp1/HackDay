#ifndef __C_SELECTOR_H__
#define __C_SELECTOR_H__

#include <Arduino.h>
#include "event_generator.h"

class C_Selector : public C_EventGenerator {
 
 public:
    // constructor 
   C_Selector(const String& argName, const unsigned int argPin, const unsigned long argDebounceDelay);
  
   void scan(void);
   byte getState();
   
 private:
   unsigned int pin;
   byte state; // debounced state
   byte prevState; // previuos read state
   unsigned long debounceTime;
   unsigned long time;

   byte volt2state(unsigned int volt);
};

#endif // __C_SELECTOR_H__

