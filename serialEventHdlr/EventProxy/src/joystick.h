#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include <Arduino.h>
#include "event_generator.h"

class Joystick : public EventGenerator {
 
 public:
    // constructor 
   Joystick(const String& Name,
		       const unsigned int Pin,
           const bool flipped = false,
           const unsigned int x_low = 0,
           const unsigned int x_mid = 512,
           const unsigned int x_hi = 1023);
   ~Joystick();

   void scan(void);
   int GetPos();
   void SetFlipped(bool flipped);
   void CalibrateHi();
   void CalibrateMid();
   void CalibrateLow();
   
 private:
   void CreateMap(unsigned int lo, unsigned int mid, unsigned int hi);
   unsigned int ReadPos();
   int Map2Pos(unsigned int ad_val);
   void Calibrate(unsigned int &v);

   unsigned int pin_;
   int pos_; // current joystick position
   bool flipped_;
   unsigned int x_low_; // ad value when joystick in "lowest" position
   unsigned int x_mid_; // ad value when joystick in "mid"/neutral position
   unsigned int x_hi_; // ad value when joystick in "highest" position

   // coefficients for mapping ad_val to pos
   float a1, b1, c1; 
   float a2, b2, c2; 
};

#endif // __JOYSTICK_H__

