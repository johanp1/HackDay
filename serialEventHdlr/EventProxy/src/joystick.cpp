#include "joystick.h"

auto constexpr k_default_idle_ad_val = 512;

//   public:
Joystick::Joystick(const String& Name,
		             const unsigned int Pin) : EventGenerator(Name), pin_(Pin)
{
   pos_ = 0;
   offset = 0;
}

Joystick::~Joystick()
{
}

// returns debounced selector state
void Joystick::scan(void)
{
   int new_pos = Map2Pos(analogRead(pin_));
   if(pos_ != new_pos)
   {
      pos_ = new_pos;
      generateEvent(pos_);
   } 
}

int Joystick::GetPos()
{
  return pos_;
}

void Joystick::Calibrate()
{
   // mean value over 3 samples
   offset = k_default_idle_ad_val - analogRead(pin_);
   offset = (offset + k_default_idle_ad_val - analogRead(pin_))/2;
   offset = (offset + k_default_idle_ad_val - analogRead(pin_))/2;
}

//  y = ax^2 + bx + c
//  y(0) = -102, y(512) = 0, y(1023) = 102, y'(512) = 0
//  0<=x<512:    y = -2/51*(x/10)^2 + 4x - 102
//  512<=x<1023: y =  2/51*(x/10)^2 - 4x + 102
int Joystick::Map2Pos(int ad_val)
{
   int ret_val = 0;
   int x = (ad_val+offset)/10; // ad_val ([0-1023]+offset)/10
   long temp = 0;

   // map to desired curv
   if (ad_val < 512)
   {
      temp = -(2*x*x)/51 + 4*x - 102;
   }
   else // 512 <= ad_val <= 1023 
   {
      temp = (2*x*x)/51 -4*x + 102;
   }
   ret_val = (int)temp;

   return ret_val;
}
