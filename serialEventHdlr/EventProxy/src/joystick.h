#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include <Arduino.h>
#include "event_generator.h"

class Joystick : public EventGenerator {
 
 public:
    // constructor 
   Joystick(const String& Name,
		       const unsigned int Pin);
   ~Joystick();

   void scan(void);
   byte getPos();
   
 private:
   unsigned int pin_;
   unsigned int pos_; // debounced state
};

#endif // __JOYSTICK_H__

