#include "receiver.h"
#include <iostream>

// constructor 
Receiver::Receiver(const String& argName) : EventGenerator(argName)
{
   recCmd = String();
}

void Receiver::scan(void)
{
   String cmd = String();
   String emptyStr = String("");
   
   if(Serial.available() > 0)
   {
      cmd = Serial.readStringUntil('\n');
      if (cmd.compareTo(emptyStr) != 0)
      {
         generateEvent(cmd);
      }
   }
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
         recCmd = "";   //clear
      }
      else
      {
        recCmd.concat(ch);
      }
   }
}