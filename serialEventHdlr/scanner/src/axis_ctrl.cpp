#include "axis_ctrl.h"
#include <iostream>

AxisCtrl::AxisCtrl(StepGen& s, float scale) : stepGen_(s), scale_(scale)
{
    stepGen_.Attach(this);
}

AxisCtrl::~AxisCtrl()
{}

void AxisCtrl::SetScale(float scale)
{
    scale_ = scale;
}

void AxisCtrl::SetSpeed(float units_per_sec)
{
    unsigned int steps_per_sec = scale_*units_per_sec;
    stepGen_.SetStepsPerSec(steps_per_sec);
}

float AxisCtrl::GetPosition()
{
    return position_;
}

void AxisCtrl::SetRelativePosition(float pos)
{
    //position_ += pos;
    // remove sign from pos
    float unsigned_scaled_pos = (pos < 0 ? -pos : pos);
    if (unsigned_scaled_pos >= 1)
    {
        stepGen_.SetDirection(pos > 0 ? direction_forward : direction_reverse);
        stepGen_.Step(unsigned_scaled_pos);
    }
}

void AxisCtrl::SetAbsolutPosition(float pos)
{
    float delta = position_ - pos;
    position_ -= delta;

    // remove sign from steps
    unsigned int steps = (delta < 0 ? -delta*scale_ : delta*scale_);
    if (steps >= 1)
    {
        stepGen_.SetDirection(delta < 0 ? direction_forward : direction_reverse);
        stepGen_.Step(steps);
    }
}

void AxisCtrl::SetHome(float pos)
{
    position_ = pos;
}

void AxisCtrl::Update()
{
    position_ += (stepGen_.GetDirection() == direction_forward ? 1 : -1)/scale_;
    //position_ += 1/scale_;
}