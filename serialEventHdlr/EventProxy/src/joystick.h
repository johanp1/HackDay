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
   int GetPos();
   
 private:
   int ReadAD();
   unsigned int pin_;
   int pos_; // debounced state
};

#endif // __JOYSTICK_H__

