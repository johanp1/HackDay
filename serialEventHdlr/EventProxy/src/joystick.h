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
   void CalibrateHi();
   void CalibrateMid();
   void CalibrateLow();
   
 private:
   void CreateMap(int lo, int mid, int hi);
   int Map2Pos(int ad_val);
   void Calibrate(int &v);

   unsigned int pin_;
   int pos_; // current joystick position

   int low_;
   int mid_;
   int hi_;

   // coefficients for mapping ad_val to pos
   float a1, b1, c1; 
   float a2, b2, c2; 
};

#endif // __JOYSTICK_H__

