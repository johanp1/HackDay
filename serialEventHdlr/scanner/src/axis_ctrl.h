#ifndef __C_AXIS_CTRL_H__
#define __C_AXIS_CTRL_H__

#include "step_gen.h"

//using milli_sec = uint16_t;
//using Pin = byte;
//enum stepRetVal { ok, busy };

//constexpr milli_sec default_t_on = 2; //5ms

class AxisCtrl
{
   public:
   AxisCtrl(const StepGen& s);
   virtual ~AxisCtrl();

   private:
   const StepGen& stepGen_;
};

#endif //__C_AXIS_CTRL_H__