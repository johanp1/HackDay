#include "joystick.h"

auto constexpr k_default_idle_ad_val = 512;

//   public:
Joystick::Joystick(const String& Name,
		             const unsigned int Pin,
                   const bool flipped,
                   const unsigned int x_low,
                   const unsigned int x_mid,
                   const unsigned int x_hi) : EventGenerator(Name), pin_(Pin), flipped_(flipped)
{
   pos_ = 0; 
   limits_.x_low = x_low;
   limits_.x_mid = x_mid;
   limits_.x_hi = x_hi;

   Calibrate(limits_.x_mid);
}

Joystick::~Joystick()
{
}

// returns debounced selector state
void Joystick::scan(void)
{
   int mapped_pos = Map2Pos(ReadPos());
   if(pos_ != mapped_pos)
   {
      pos_ = mapped_pos;
      generateEvent(pos_);
   } 
}

int Joystick::GetPos()
{
  return pos_;
}

void Joystick::SetFlipped(bool flipped)
{
   flipped_ = flipped;
}

void Joystick::Calibrate(JoystickLimitPosition pos)
{
   if (pos == low)
   {
      Calibrate(limits_.x_low);
   }
   if (pos == mid)
   {
      Calibrate(limits_.x_mid);
   }
   if (pos == hi)
   {
      Calibrate(limits_.x_hi);
   }
}

const JoystickLimits& Joystick::GetLimits()
{
   return limits_;
}

// calculates a1, a2, b1, b2, c1, c2 in
// y1 = a1x^2 + b1x + c1, 0 <= x < 51
// y2 = a2x^2 + b2x + c2, 51 <= x <= 102
//
// y1(x_low) = -100, y1(x_mid) = 0, y1'(x_mid) = 0
// y2(x_mid) = 0, y2'(x_mid) = 0, y2(high) = 100
void Joystick::CreateMap()
{
   // reduce resulotion
   int x_low = limits_.x_low/10;
   int x_mid = limits_.x_mid/10;
   int x_hi = limits_.x_hi/10;

   // coefficians for 0 <= x < 51
   a1 = -100.0f/(float)(x_low*x_low-x_mid*x_mid - 2*x_mid*(x_low-x_mid)); 
   b1 = -2.0f*a1*x_mid;
   c1 = a1*x_mid*x_mid;

   // coefficians for  51 <= x <= 102
   a2 = 100.0f/(float)(x_hi*x_hi-x_mid*x_mid - 2*x_mid*(x_hi-x_mid));
   b2 = -2*a2*x_mid;
   c2 = a2*x_mid*x_mid;   
}

unsigned int Joystick::ReadPos()
{
   unsigned int pos = analogRead(pin_);
   return flipped_ ? limits_.x_low + limits_.x_hi - pos : pos; 
}

//  y = ax^2 + bx + c
//  x_low <= x < x_mid:   y1(x)
//  x_mid <= x <= high: y2(x)
int Joystick::Map2Pos(unsigned int ad_val)
{
   int ret_val = 0;
   int x = ad_val/10;; // ad_val ([0-1023]+offset_mid)/10
   long temp = 0;

   if (ad_val < limits_.x_mid)
   {
      temp = a1*x*x + b1*x + c1;
   }
   else // x_mid_ <= ad_val <= x_hi_ 
   {
      temp = a2*x*x + b2*x + c2;
   }
   ret_val = (int)temp;

   return ret_val;
}

void Joystick::Calibrate(unsigned int &v)
{
   // mean value over 3 samples
   v =  ReadPos();
   v = (v + ReadPos())/2;
   v = (v + ReadPos())/2;
   
   CreateMap();
}
