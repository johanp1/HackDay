#ifndef __C_AXIS_CTRL_H__
#define __C_AXIS_CTRL_H__

#include "step_gen.h"

constexpr float kDegreesPerRev = 360;

// full-step 400 steps/rev for motor 1:4 ratio for axis => 1600 steps/rev => 0.225 degrees/step
enum AxisCrtlStatus { kIdle, kMoving };
enum MoveRequestStatus {kOk, kNotOk};

using Position = float;

class AxisCtrl : public StepObserver
{
   public:
   AxisCtrl(StepGen& s, float scale = 1.0f);
   virtual ~AxisCtrl();

   void SetScale(float scale);
   void SetSpeed(float units_per_sec);
   virtual Position GetPosition();
   virtual MoveRequestStatus MoveToRelativePosition(Position pos);
   virtual MoveRequestStatus MoveToAbsolutPosition(Position pos);
   virtual void SetHome(float offset = 0.0f);
   virtual AxisCrtlStatus GetStatus();
   void Update() override;
   
   protected:
   float scale_ = 1.0f; // step/degree
   Position position_ = 0.0f;
   StepGen& stepGen_;

   MoveRequestStatus MoveRequest(float pos);
};

class RotaryAxisCtrl : public AxisCtrl
{
   public:
   RotaryAxisCtrl(StepGen& s, float scale);
   ~RotaryAxisCtrl();
   
   MoveRequestStatus MoveToAbsolutPosition(Position pos) override;

   void SetHome(float offset = 0.0f) override;
   void Update() override;
};

#endif //__C_AXIS_CTRL_H__