#include "axis_ctrl.h"
#include "Arduino.h"

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

Position AxisCtrl::GetPosition()
{
    return position_;
}

MoveRequestStatus AxisCtrl::MoveToRelativePosition(Position pos)
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

MoveRequestStatus AxisCtrl::MoveToAbsolutPosition(Position pos)
{
    MoveRequestStatus retVal = kOk;

    if (!stepGen_.IsBusy())
    {
        float delta = pos - position_;

        // calculate number of steps to request, unsigned...
        unsigned int steps = abs(delta)*scale_ + 0.5f;
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

            stepGen_.SetDirection(delta > 0 ? direction_forward : direction_reverse);
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

void AxisCtrl::Update()
{
    position_ += (stepGen_.GetDirection() == direction_forward ? 1 : -1)/scale_;
}