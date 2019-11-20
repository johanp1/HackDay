#include "pulse_stretcher.h"
#include <iostream>

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
        cout << "start stretching\n";
    }

    output = v;
    if (stretching)
    {
        output = HIGH;
        cout << "stretching\n";
    }

    prev = v;
    cout << "output: " << output << "\n";
    return output;
}