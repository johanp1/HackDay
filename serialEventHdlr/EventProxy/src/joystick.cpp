#include "joystick.h"
#include <EEPROM.h>

auto constexpr k_default_idle_ad_val = 512;
auto constexpr k_ee_address_low_value = 0;
auto constexpr k_ee_address_hi_offset = sizeof(int);

//   public:
Joystick::Joystick(const String& Name,
		             const unsigned int Pin,
                   const  unsigned int eeBaseAdress) : EventGenerator(Name), pin_(Pin), ee_base_address_(eeBaseAdress)
{
   pos_ = 0; 
   
   EEPROM.get(ee_base_address_, low_);
   EEPROM.get(ee_base_address_ + k_ee_address_hi_offset, hi_);

   Calibrate(mid_);
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
   Calibrate(mid_);
}

void Joystick::CalibrateLow()
{
   Calibrate(low_);
   EEPROM.put(ee_base_address_, low_);
}

void Joystick::CalibrateHi()
{
   Calibrate(hi_);
   EEPROM.put(ee_base_address_ + k_ee_address_hi_offset, hi_);
}

void Joystick::Calibrate(int &v)
{
   // mean value over 3 samples
   v =  analogRead(pin_);
   v = (v + analogRead(pin_))/2;
   v = (v + analogRead(pin_))/2;
   
   // save low_ to eeprom

   CreateMap(low_, mid_, hi_);
}

// calculates a1, a2, b1, b2, c1, c2 in
// y1 = a1x^2 + b1x + c1, 0 <= x < 51
// y2 = a2x^2 + b2x + c2, 51 <= x <= 102
//
// y1(low) = -100, y1(mid) = 0, y1'(mid) = 0
// y2(mid) = 0, y2'(mid) = 0, y2(high) = 100
void Joystick::CreateMap(int low_val, int mid_val, int hi_val)
{
   // reduce resulotion
   int low = low_val/10;
   int mid = mid_val/10;
   int hi = hi_val/10;

   // coefficians for 0 <= x < 51
   a1 = -100.0f/(float)(low*low-mid*mid - 2*mid*(low-mid)); 
   b1 = -2*a1*mid;
   c1 = a1*mid*mid;

   // coefficians for  51 <= x <= 102
   a2 = 100.0f/(float)(hi*hi-mid*mid - 2*mid*(hi-mid));
   b2 = -2*a2*mid;
   c2 = a2*mid*mid;   
}

//  y = ax^2 + bx + c
//  low <= x < mid:   y1(x)
//  mid <= x <= high: y2(x)
int Joystick::Map2Pos(int ad_val)
{
   int ret_val = 0;
   int x = ad_val/10; // ad_val ([0-1023]+offset_mid)/10
   long temp = 0;

   if (ad_val < mid_)
   {
      temp = a1*x*x + b1*x + c1;
   }
   else // 512 <= ad_val <= 1023 
   {
      temp = a2*x*x + b2*x + c2;
   }
   ret_val = (int)temp;

   return ret_val;
}
