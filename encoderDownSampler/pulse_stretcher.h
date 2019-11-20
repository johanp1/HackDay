#ifndef __C_PULSE_STRETCHER_H__
#define __C_PULSE_STRETCHER_H__

#include "arduino.h"

class PulseStretcher
{
    public:
    PulseStretcher(int msDuration);
    int update(int v);

    private:
    int prev;
    int stretchDuration;
    int stretchStartTime;
    int output;
    bool stretching;
};

#endif