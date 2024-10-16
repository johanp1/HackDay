#include "axis_ctrl.h"
#include "Arduino.h"

AxisCtrl::AxisCtrl(StepGen& s, float scale) : stepGen_(s), scale_(scale)
{
    stepGen_.AttachStepObserver(&stepUpdater_);
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

Position AxisCtrl::GetPosition()
{
    return position_;
}

MoveRequestStatus AxisCtrl::MoveToRelativePosition(Position pos)
{
    return MoveRequest(pos);
}

MoveRequestStatus AxisCtrl::MoveToAbsolutPosition(Position pos)
{
    float delta = pos - position_;
    return MoveRequest(delta);
}

MoveRequestStatus AxisCtrl::MoveRequest(float pos)
{
    MoveRequestStatus retVal = kOk;
    
    if (!stepGen_.IsBusy())
    {
        unsigned int steps = abs(pos)*scale_ + 0.5f; // remove sign from pos
        if (steps >= 1)
        {
            if (steps >= 20)
            {
                stepGen_.SetUseRamping(true);
            }
            else
            {
                stepGen_.SetUseRamping(false);
            }

            stepGen_.SetDirection(pos > 0 ? direction_forward : direction_reverse);
            stepGen_.Step(steps);
        }
    }
    else
    {
        retVal = kNotOk;
    }

    return retVal;
}

// will set current position to <offset>, i.e. new home will be <offset> away from current pos
void AxisCtrl::SetHome(float offset)
{
    position_ = offset;
}

AxisCrtlStatus AxisCtrl::GetStatus()
{
    return stepGen_.IsBusy() ? kMoving : kIdle;
}

void AxisCtrl::UpdatePosition()
{
    position_ += (stepGen_.GetDirection() == direction_forward ? 1 : -1)/scale_;
}

void AxisCtrl::UpdatePositionWrapper(AxisCtrl* a)
{
    if (a != nullptr)
    {
        a->UpdatePosition();
    }
}

RotaryAxisCtrl::RotaryAxisCtrl(StepGen& s, float scale) : AxisCtrl(s, scale) {}

RotaryAxisCtrl::~RotaryAxisCtrl()
{}

// will set current position to <offset>, i.e. new home will be <offset> away from current pos
void RotaryAxisCtrl::SetHome(float offset)
{
    position_ = fmod(offset, kDegreesPerRev);
}

void RotaryAxisCtrl::UpdatePosition()
{
    position_ += (stepGen_.GetDirection() == direction_forward ? 1 : -1)/scale_;
    position_ = fmod(position_, kDegreesPerRev);
}

// for rotary axis, absolut moves will take the shortest way to target pos
MoveRequestStatus RotaryAxisCtrl::MoveToAbsolutPosition(Position pos)
{
    pos = fmod(pos, kDegreesPerRev);

    // if doing clock-wise move, cc_delta is the distance.
    // the counter-clock-wise move distance is 360-cc_delta
    float delta_distance = pos - position_; // positve values is counter clock-wise moves
    float cc_distance = delta_distance >= 0 ? delta_distance : (kDegreesPerRev + delta_distance);
    float ccw_distance = (kDegreesPerRev - cc_distance);
    float move_req = cc_distance <= ccw_distance ? cc_distance : -ccw_distance;
    
    return MoveRequest(move_req);
}