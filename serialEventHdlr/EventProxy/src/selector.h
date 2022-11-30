#ifndef __SELECTOR_H__
#define __SELECTOR_H__

#include <Arduino.h>
#include "event_generator.h"

constexpr int kDefaultLimit = 60u;
constexpr byte kDefaultNumberOfStates = 4;
constexpr unsigned int kDefaultStateVals[4] = {255u, 340u, 512u, 1024u};
constexpr byte kUndefinedState = 255;

struct SelectorStatesType
{
   byte numberOfStates;
   int* stateADValues;
};
using SelectorStates = SelectorStatesType;

class Selector : public EventGenerator {
 
 public:
    // constructor 
   Selector(const String& argName,
		       const unsigned int argPin,
		       const unsigned long argDebounceDelay,
             const unsigned int stateVolts[] = kDefaultStateVals,
             const byte numberOfStates = kDefaultNumberOfStates,
             const byte stateValueUncertainty = kDefaultLimit);
   ~Selector();

   void scan(void);
   byte getState();
   
 private:
   unsigned int pin;
   byte state; // debounced state
   byte prevState; // previuos read state
   unsigned long debounceTime;
   unsigned long time;
   byte stateValueUncertainty_;
   SelectorStates states_;

   byte volt2state(unsigned int volt);
};

#endif // __SELECTOR_H__

