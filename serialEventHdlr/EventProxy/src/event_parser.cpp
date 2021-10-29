#include "event_parser.h"
#include "Arduino.h"

EventParser::EventParser()
{
   nbrOfCmds = 0;
}

void EventParser::HandleEvent(C_Event& e)
{
   String evData = e.serializeData();
   ParseEvent(evData);
}

void EventParser::ParseEvent(String& unparsedData)
{
   if(nbrOfCmds > 0)
   {
      //fetch command
      for (int i = 0; i < nbrOfCmds; i++)
      {
         // does the unparsed data contian(starts with) some sort of command 
         bool isAccepted = unparsedData.startsWith(acceptedCmds[i]->cmd);
         if (isAccepted) //data starts with a command
         {
            String data = String("");

            // if the unparsed data contains more than cmd, split out the data-part from the cmd-part
            // format is "cmd_data"
            if ((unparsedData.length() > acceptedCmds[i]->cmd.length() + 1) && // does it contain data
                (unparsedData.charAt(acceptedCmds[i]->cmd.length()) == '_'))   // is the char after the "cmd" a '_'
            {
               data = unparsedData.substring(acceptedCmds[i]->cmd.length()+1); // take the data part, not the "cmd_"-part

               acceptedCmds[i]->execute(data);
            }
            if (unparsedData.length() == acceptedCmds[i]->cmd.length())
            {
               acceptedCmds[i]->execute(data);
            }
         }
      }
   }
}

void EventParser::AddAcceptedCmd(ParserFunctionoid& pf)
{
   if (nbrOfCmds < c_maxNbrOfAcceptedCmds)
   {
      acceptedCmds[nbrOfCmds] = &pf;
      nbrOfCmds++;
   }   
}

int EventParser::GetNbrOfAcceptedCmds()
{
   return nbrOfCmds;
}