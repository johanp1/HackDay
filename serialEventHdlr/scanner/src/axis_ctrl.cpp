#include "axis_ctrl.h"
#include <iostream>

AxisCtrl::AxisCtrl(StepGen& s, float scale) : stepGen_(s), scale_(scale) {}

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
    position_ += pos;

    // remove sign from pos
    float unsigned_pos = (pos < 0 ? -pos : pos);
    stepGen_.Step(unsigned_pos*scale_);
}

void AxisCtrl::SetAbsolutPosition(float pos)
{
    float delta = position_ - pos;
    position_ -= delta;

    // remove sign from pos
    unsigned int steps = (delta < 0 ? -delta*scale_ : delta*scale_);
    if (steps > 1)
    {
        stepGen_.Step(steps);
    }
}