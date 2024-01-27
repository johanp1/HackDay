#ifndef __EXTRUDER_H__
#define __EXTRUDER_H__
#include "Arduino.h"

class Extruder
{
   public:
   Extruder(int tempSensPin, int pwmPin);
   void SetDebug(bool d);
   void SetEnabled(bool e);
   void SetTempPwmDuty(int d);
   int ReadTemp();
   bool IsEnabled();
   
   private:
   bool debug_;
   bool enabled_;
   int tempSensPin_;
   int pwmPin_;
};

#endif
