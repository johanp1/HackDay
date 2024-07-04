#include "joystick.h"

auto constexpr k_default_idle_ad_val = 512;
auto constexpr k_position_max = 100;
auto constexpr k_position_min = -100;

//   public:
Joystick::Joystick(const String& Name,
		             const unsigned int Pin,
                   const bool flipped,
                   const AdValue x_low,
                   const AdValue x_hi) : EventGenerator(Name), pin_(Pin), flipped_(flipped)
{
   pos_ = 0; 
   limits_.low = x_low;
   limits_.hi = x_hi;

   Calibrate(mid);
}

Joystick::~Joystick()
{
}

// returns debounced selector state
void Joystick::scan(void)
{
   auto mapped_pos = map_.Map2Pos(Read());
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
   // mean value over 3 samples
   AdValue v =  Read();
   v = (v + Read())/2;
   v = (v + Read())/2;

   if (pos == low)
   {
      limits_.low = v;
   }
   if (pos == mid)
   {
      limits_.mid = v;
   }
   if (pos == hi)
   {
      limits_.hi = v;
   }

   map_.CalcMap(limits_.low, limits_.mid, limits_.hi);
}

const MapPoints& Joystick::GetLimits()
{
   return limits_;
}

AdValue Joystick::Read()
{
   AdValue pos = analogRead(pin_);
   return flipped_ ? limits_.low + limits_.hi - pos : pos; 
}

PositionMap::PositionMap(const AdValue low, const AdValue mid, const AdValue hi)
{
   mid_ = mid;
   CalcMap(low, mid, hi);
}

PositionMap::~PositionMap()
{
}

// function for creating mapping coefficients.
// values read from the AD converter [0, 1023] needs to be mapped 
// to a value between [-100, 100].
//
// the calculated coefficients assumes the mapping function is a 2nd order polynomial.
// the mapping is split according to:
// y1 = a1x^2 + b1x + c1, low <= x < mid
// y2 = a2x^2 + b2x + c2, mid <= x <= high
//
// y1(x_low) = -100, y1(x_mid) = 0, y1'(x_mid) = 0
// y2(x_mid) = 0, y2'(x_mid) = 0, y2(high) = 100
void PositionMap::CalcMap(const AdValue low, const AdValue mid, const AdValue hi)
{
   // reduce resulotion
   auto x_low = low/10;
   auto x_mid = mid/10;
   auto x_hi = hi/10;

   // coefficians for 0 <= x < 51
   a1 = k_position_min/(float)(x_low*x_low-x_mid*x_mid - 2*x_mid*(x_low-x_mid)); 
   b1 = -2.0f*a1*x_mid;
   c1 = a1*x_mid*x_mid;

   // coefficians for  51 <= x <= 102
   a2 = k_position_max/(float)(x_hi*x_hi-x_mid*x_mid - 2*x_mid*(x_hi-x_mid));
   b2 = -2*a2*x_mid;
   c2 = a2*x_mid*x_mid;   
}

void CalcMap(const MapPoints& map_points);

// function for mapping the values read from the AD converter to a joystick position
// as per the pre-defined mapp calculated with CreateMap()
Position PositionMap::Map2Pos(AdValue v)
{
   Position ret_val = 0;
   AdValue x = v/10; // ad_val ([0-1023]+offset_mid)/10
   long temp = 0;

   if (v < mid_)
   {
      temp = a1*x*x + b1*x + c1;
   }
   else // mid_ <= ad_val <= x_hi_ 
   {
      temp = a2*x*x + b2*x + c2;
   }

   //saturate
   temp = temp > k_position_max ? k_position_max : temp;
   temp = temp < k_position_min ? k_position_min : temp;

   ret_val = (Position)temp;

   return ret_val;
}