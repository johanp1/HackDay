#ifndef __SELECTOR_H__
#define __SELECTOR_H__

#include <Arduino.h>
#include "event_generator.h"

constexpr byte numberOfStates_ = 4;

class Selector : public EventGenerator {
 
 public:
    // constructor 
   Selector(const String& argName, const unsigned int argPin, const unsigned long argDebounceDelay);
   Selector(const String& argName,
		       const unsigned int argPin,
		       const unsigned long argDebounceDelay,
             const unsigned int stateVolts[numberOfStates_]);

   void scan(void);
   byte getState();
   
 private:
   unsigned int pin;
   byte state; // debounced state
   byte prevState; // previuos read state
   unsigned long debounceTime;
   unsigned long time;

   byte volt2state(unsigned int volt);

   
   unsigned int stateVals_[4] = {255u, 340u, 512u, 1024u}; //default values, 1024 = Vref(5V)
};

#endif // __SELECTOR_H__

