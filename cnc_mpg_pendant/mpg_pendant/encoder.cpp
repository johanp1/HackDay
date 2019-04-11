#include "encoder.h"

//  public:

// constructor : sets pins as inputs and turns on pullup resistors
C_RotaryEncoder::C_RotaryEncoder( const String& argName, int argClkPin, int argDtPin) : C_EventGenerator(argName), clkPin ( argClkPin), dtPin( argDtPin ) 
{
   // set pin a and b to be input
   pinMode(clkPin, INPUT);
   pinMode(dtPin, INPUT);
   // and turn on pull-up resistors
   digitalWrite(clkPin, HIGH);
   digitalWrite(dtPin, HIGH);
}

// call this from your interrupt function
void C_RotaryEncoder::update(void) 
{
   if (digitalRead(clkPin))
   {
      digitalRead(dtPin) ? position++ : position--;
   }
   else 
   {
      digitalRead(dtPin) ? position-- : position++;
   }
   generateEvent(position);
}

// returns current position
unsigned int C_RotaryEncoder::getPosition ()
{
   return position;
}

// set the position value

void C_RotaryEncoder::setPosition ( unsigned int p)
{
   position = p;
}
