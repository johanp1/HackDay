#include "receiver.h"

// constructor 
Receiver::Receiver(const String& argName) : EventGenerator(argName)
{
   recCmd = String();
}

void Receiver::scan(void)
{
}

void Receiver::serialEvent()
{
   char ch;
   String emptyStr = String("");

   while(Serial.available() > 0)
   {
      ch = (char)Serial.read();

      if (ch == '\n')
      {
         if(recCmd.compareTo(emptyStr) != 0)
         {
            generateEvent(recCmd);
         }
         recCmd = "";   //clear, ready for new message
      }
      else
      {
        recCmd.concat(ch);
      }
   }
}