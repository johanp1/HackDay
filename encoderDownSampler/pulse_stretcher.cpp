#include "pulse_stretcher.h"

PulseStretcher::PulseStretcher(int msDuration) : stretchDuration (msDuration)
{
    prev = 0;
    output = 0;
    stretching = false;
}

int PulseStretcher::update(int v)
{
    //detect negative flank, thats when we start stretching
    if ((prev == 1) && (v == 0))
    {
        stretching = true;
        stretchStartTime = micros();
    }

    output = v;
    if (stretching)
    {
        int timePassed;

        timePassed = (int)(micros() - stretchStartTime); // will handle overflow too

        if (timePassed >= stretchDuration)
        {
            stretching = false;
            output = LOW;
        }
        else
        {
            output = HIGH;
        }
        
    }

    prev = v;

    return output;
}