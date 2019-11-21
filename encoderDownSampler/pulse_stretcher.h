#ifndef __C_PULSE_STRETCHER_H__
#define __C_PULSE_STRETCHER_H__

#include "arduino.h"

class PulseStretcher
{
    public:
    PulseStretcher(int usDuration);
    int update(int v);

    private:
    int prev;
    int stretchDuration;
    unsigned long stretchStartTime;
    int output;
    bool stretching;
};

#endif