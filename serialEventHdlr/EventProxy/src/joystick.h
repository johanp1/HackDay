#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include <Arduino.h>
#include "event_generator.h"

using AdValue = unsigned int; //type for A/D value
using Position = int; // type for joystick position

struct MapPointsStruct
{
  AdValue low; // ad value when joystick in "lowest" position
  AdValue mid; // ad value when joystick in "mid"/neutral position
  AdValue hi;  // ad value when joystick in "highest" position
};
using MapPoints = MapPointsStruct;

enum JoystickLimitPositionEnum
{
  low = 0,
  mid = 1,
  hi = 2,
};
using JoystickLimitPosition = JoystickLimitPositionEnum;

class PositionMap
{
  public:
  PositionMap(const AdValue low = 0, const AdValue mid = 512, const AdValue hi = 1023);
  virtual ~PositionMap();

  void CalcMap(const AdValue low, const AdValue mid, const AdValue hi);
  void CalcMap(const MapPoints& map_points);
  Position Map2Pos(AdValue ad_val);

  private:
  AdValue mid_;

  // coefficients for mapping ad_val to pos
  float a1, b1, c1; 
  float a2, b2, c2; 
};

class Joystick : public EventGenerator { 
 public:
   Joystick(const String& Name,
		       const unsigned int Pin,
           const bool flipped = false,
           const AdValue x_low = 0,
           const AdValue x_hi = 1023);
   ~Joystick();

   void scan(void);
   int GetPos();
   void SetFlipped(bool flipped);
   void Calibrate(JoystickLimitPosition pos);
   const MapPoints& GetLimits();

 private:
   AdValue Read();

   unsigned int pin_;
   Position pos_; // current joystick position
   bool flipped_;
   MapPoints limits_;
   PositionMap map_;
};

#endif // __JOYSTICK_H__

