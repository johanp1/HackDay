#include "encoder.h"

//  public:

// constructor : sets pins as inputs and turns on pullup resistors
RotaryEncoder::RotaryEncoder( const String& argName, int argClkPin, int argDtPin) : EventGenerator(argName), clkPin ( argClkPin), dtPin( argDtPin ) 
{
   // set pin a and b to be input with pull up enabled
   pinMode(clkPin, INPUT_PULLUP);
   pinMode(dtPin, INPUT_PULLUP);
   
   position = 0;
}

void RotaryEncoder::update(void) 
{
   digitalRead(dtPin) ? position++ : position--;
   generateEvent((unsigned int)position);
}

int RotaryEncoder::getPosition ()
{
   return position;
}

void RotaryEncoder::clearPosition()
{
   position = 0;
}

void RotaryEncoder::scan(void)
{
   update();
}