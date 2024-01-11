#include "joystick.h"

//   public:
Joystick::Joystick(const String& Name,
		       const unsigned int Pin) : EventGenerator(Name), pin_(Pin)
{
   pos_ = 0;
}

Joystick::~Joystick()
{
}

// returns debounced selector state
void Joystick::scan(void)
{
   byte pos_ = (unsigned int)analogRead((int)pin_); // read pin
}

byte Joystick::getPos()
{
  return pos_;
}

