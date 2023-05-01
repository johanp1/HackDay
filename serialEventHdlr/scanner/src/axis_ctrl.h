#ifndef __C_AXIS_CTRL_H__
#define __C_AXIS_CTRL_H__

#include "step_gen.h"

// full-step 400 steps/rev for motor 1:4 ratio for axis => 1600 steps/rev => 0.225 degrees/step

class AxisCtrl
{
   public:
   AxisCtrl(StepGen& s, float scale = 1.0f);
   virtual ~AxisCtrl();

   void SetScale(float scale);
   void SetSpeed(float units_per_sec);
   float GetPosition();
   void SetRelativePosition(float pos);
   void SetAbsolutPosition(float pos);

   //void SetHome(float pos = 0.0f);

   private:
   float scale_ = 1.0f; // step/degree
   float position_ = 0.0f;
   StepGen& stepGen_;
};

#endif //__C_AXIS_CTRL_H__