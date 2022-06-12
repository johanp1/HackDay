#ifndef __C_SELECTOR2_H__
#define __C_SELECTOR2_H__

#include <Arduino.h>
#include "event_generator.h"

class Selector2 : public EventGenerator {
 
 public:
    // constructor 
   Selector2(const String& argName, 
            const unsigned int argPin1,
            const unsigned int argPin2,
            const unsigned int argPin3,
            const unsigned long argDebounceDelay);
  
   void scan(void);
   
 private:
   unsigned int pin1;
   unsigned int pin2;
   unsigned int pin3;
   byte state; // debounced state
   byte prevState; // previuos read state
   unsigned long debounceTime;
   unsigned long time;
};

#endif // __C_SELECTOR_H__
