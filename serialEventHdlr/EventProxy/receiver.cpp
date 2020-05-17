#include "receiver.h"

// constructor 
Receiver::Receiver(const String& argName) : EventGenerator(argName) { }

void Receiver::scan(void)
{
   String cmd;

   if(Serial.available() > 0)
   {
      cmd = Serial.readStringUntil('\n');
      generateEvent(12);
   }
}