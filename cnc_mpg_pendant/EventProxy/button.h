 #ifndef __C_BUTTON_H__
#define __C_BUTTON_H__

#include <Arduino.h>
#include "event_generator.h"

class C_Button : public C_EventGenerator {
 
 public:
   C_Button(const String& argName, const int argPin, const unsigned long argDebounceDelay);

   void scan(void);
   unsigned int getState();
   
 private:
   int pin;
   unsigned int state; // debounced buttons tate
   unsigned int prevState; // previuos read button state
   unsigned long debounceTime;
   unsigned long time;
};

#endif // __BUTTON_H__

