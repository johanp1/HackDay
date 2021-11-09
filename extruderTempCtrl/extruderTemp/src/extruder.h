#ifndef __EXTRUDER_H__
#define __EXTRUDER_H__
#include "Arduino.h"

class Extruder
{
   public:
   Extruder(int tempSensPin_, int pwmPin_);
   void SetDebug(bool d);
   void SetTempPwmDuty(int d);
   int ReadTemp();

   private:
   bool debug;
   int tempSensPin;
   int pwmPin;
};

#endif
