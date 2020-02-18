#include "encoder.h"

//  public:

// constructor : sets pins as inputs and turns on pullup resistors
RotaryEncoder::RotaryEncoder( const String& argName, int argClkPin, int argDtPin) : EventGenerator(argName), clkPin ( argClkPin), dtPin( argDtPin ) 
{
   // set pin a and b to be input
   pinMode(clkPin, INPUT);
   pinMode(dtPin, INPUT);
   // and turn on pull-up resistors
   digitalWrite(clkPin, HIGH);
   digitalWrite(dtPin, HIGH);

   position = 0;
}

// call this from your interrupt function
void RotaryEncoder::update(void) 
{
   digitalRead(dtPin) ? position++ : position--;
   generateEvent((unsigned int)position);
}

// returns current position
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
}