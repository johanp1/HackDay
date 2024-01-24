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
   void Calibrate();
   
 private:
   int Map2Pos(int ad_val);
   unsigned int pin_;
   int pos_; // debounced state
   int offset;
};

#endif // __JOYSTICK_H__

