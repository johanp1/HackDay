#include "receiver.h"

// constructor 
Receiver::Receiver(const String& argName) : EventGenerator(argName)
{
   recCmd = String();
}

void Receiver::scan(void)
{
   serialEvent();
}

// try to de-serialize event. event format is [<event name>_<event_data>]
void Receiver::serialEvent()
{
   char ch;

   while(Serial.available() > 0)
   {
      ch = (char)Serial.read();

      if (ch == '\n')
      {
         if(recCmd.compareTo("") != 0)
         {
            bool event_generated = false;
            int i = 1;
            // '\n' marks the end of the received data
            // try to separate the event name from the event data
            // i.e. find the first '_', split name and data from that point
            while ((!event_generated) && (i < recCmd.length()))
            {
               if ((recCmd.charAt(i) == '_') && (i < recCmd.length()-1))
               {
                  generateEvent(recCmd.substring(0, i), recCmd.substring(i+1));
                  event_generated = true;
               }
               i++;
            }
            
            // if the event didn't consist of event_name and event_data
            // just send it as a data-less event (name only)
            if (!event_generated)
            {
               // do some consistency check
               if ((recCmd.charAt(0) != '_') && (recCmd.charAt(recCmd.length()-1) != '_'))
               {
                  generateEvent(recCmd, "");
               }
            }
         }
         recCmd = "";   //clear, ready for new message
      }
      else
      {
        recCmd.concat(ch);
      }
   }
}