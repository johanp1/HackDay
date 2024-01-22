#include "joystick.h"
#include <iostream>
#include <string>
//   public:
Joystick::Joystick(const String& Name,
		             const unsigned int Pin) : EventGenerator(Name), pin_(Pin)
{
   pos_ = 0;
}

Joystick::~Joystick()
{
}

// returns debounced selector state
void Joystick::scan(void)
{
   int new_pos = ReadAD();
   if(pos_ != new_pos)
   {
      pos_ = new_pos;
      generateEvent(pos_);
   } 
}

byte Joystick::GetPos()
{
  return pos_;
}


//  y = ax^2 + bx + c
//  y(0) = -102, y(512) = 0, y(1023) = 102, y'(512) = 0
//  0<=x<512:    y = -2/51*(x/10)^2 + 4x - 102
//  512<=x<1023: y =  2/51*(x/10)^2 - 4x + 102
int Joystick::ReadAD()
{
   int ret_val = 0;
   unsigned int ad_val = analogRead(pin_); // read pin [0-1023]
   long temp = 0;

   // map to desired curv
   if (ad_val < 512)
   {
      temp = -(2*(ad_val/10)*(ad_val/10))/51 + 4*ad_val/10 - 102;
   }
   else // 512 <= ad_val <= 1023 
   {
      temp = (2*(ad_val/10)*(ad_val/10))/51 -4*ad_val/10 + 102;
   }
   ret_val = (int)temp;

   return ret_val;
}
