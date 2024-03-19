#include "joystick.h"

auto constexpr k_default_idle_ad_val = 512;
auto constexpr k_ee_address_low_value = 0;
auto constexpr k_ee_address_hi_offset = sizeof(int);

//   public:
Joystick::Joystick(const String& Name,
		             const unsigned int Pin,
                   const bool flipped,
                   const unsigned int x_low,
                   const unsigned int x_mid,
                   const unsigned int x_hi) : EventGenerator(Name), pin_(Pin), flipped_(flipped), x_low_(x_low), x_mid_(x_mid), x_hi_(x_hi)
{
   pos_ = 0; 

   Calibrate(x_mid_);
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

void Joystick::CalibrateMid()
{
   Calibrate(x_mid_);
}

void Joystick::CalibrateLow()
{
   Calibrate(x_low_);
}

void Joystick::CalibrateHi()
{
   Calibrate(x_hi_);
}

void Joystick::Calibrate(unsigned int &v)
{
   // mean value over 3 samples
   v =  analogRead(pin_);
   v = (v + analogRead(pin_))/2;
   v = (v + analogRead(pin_))/2;
   
   CreateMap(x_low_, x_mid_, x_hi_);
}

// calculates a1, a2, b1, b2, c1, c2 in
// y1 = a1x^2 + b1x + c1, 0 <= x < 51
// y2 = a2x^2 + b2x + c2, 51 <= x <= 102
//
// y1(x_low) = -100, y1(x_mid) = 0, y1'(x_mid) = 0
// y2(x_mid) = 0, y2'(x_mid) = 0, y2(high) = 100
void Joystick::CreateMap(unsigned int low_val, unsigned int mid_val, unsigned int hi_val)
{
   // reduce resulotion
   int x_low = low_val/10;
   int x_mid = mid_val/10;
   int x_hi = hi_val/10;

   // coefficians for 0 <= x < 51
   a1 = -100.0f/(float)(x_low*x_low-x_mid*x_mid - 2*x_mid*(x_low-x_mid)); 
   b1 = -2.0f*a1*x_mid;
   c1 = a1*x_mid*x_mid;

   // coefficians for  51 <= x <= 102
   a2 = 100.0f/(float)(x_hi*x_hi-x_mid*x_mid - 2*x_mid*(x_hi-x_mid));
   b2 = -2*a2*x_mid;
   c2 = a2*x_mid*x_mid;   
}

//  y = ax^2 + bx + c
//  x_low <= x < x_mid:   y1(x)
//  x_mid <= x <= high: y2(x)
int Joystick::Map2Pos(unsigned int ad_val)
{
   int ret_val = 0;
   int x = ad_val/10;; // ad_val ([0-1023]+offset_mid)/10
   long temp = 0;

   if (ad_val < x_mid_)
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
