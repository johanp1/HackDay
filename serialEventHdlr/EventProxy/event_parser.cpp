#include "event_parser.h"
#include "Arduino.h"

void CmdFunctionMapper::execute(String& _parsedData)
{
   pf->execute(_parsedData);
}

EventParser::EventParser()
{
   nbrOfAcceptedCmds = 0;
}

void EventParser::handleEvent(C_Event& e)
{
   String evData = e.serializeData();
   parseEvent(evData);
}

void EventParser::parseEvent(String& unparsedData)
{
   if(nbrOfAcceptedCmds > 0)
   {
      //fetch command
      for (int i = 0; i < nbrOfAcceptedCmds; i++)
      {
         // does the unparsed data contian(starts with) some sort of command 
         bool isAccepted = unparsedData.startsWith(acceptedCmds[i].cmd);
         if (isAccepted) //data starts with a command
         {
            String data = String("");
            // if the unparsed data contains more than cmd, split out the data-part from the cmd-part
            if (unparsedData.length() >= acceptedCmds[i].cmd.length())
            {
               data = unparsedData.substring(acceptedCmds[i].cmd.length());
            }
            acceptedCmds[i].execute(data);
         }
      }
   }
}

void EventParser::addAcceptedCmd(String& cmd, ParserFunctionoid& pf)
{
   if (nbrOfAcceptedCmds < MAX_NBR_OF_ACCEPTED_CMDS)
   {
      acceptedCmds[nbrOfAcceptedCmds] = CmdFunctionMapper(cmd, &pf);
      nbrOfAcceptedCmds++;
   }   
}

int EventParser::getNbrOfAcceptedCmds()
{
   return nbrOfAcceptedCmds;
}