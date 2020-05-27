#include "event_parser.h"
#include "Arduino.h"
#include <iostream>
void CmdFunctionMapper::execute(String& _parsedData)
{
   pf.execute(_parsedData);
}

EventParser::EventParser(void)
{
}

void EventParser::handleEvent(C_Event& e)
{
   String evData = e.serializeData();
   parseEvent(evData);
}

void EventParser::parseEvent(String& unparsedData)
{
   if(!acceptedCmds.empty())
   {
      //fetch command
      for (int i = 0; i < (int)acceptedCmds.size(); i++)
      {
         bool startsWithCmd = unparsedData.startsWith(acceptedCmds[i].cmd);
         if (startsWithCmd) //data starts with a command
         {
            String data = String("");
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
   acceptedCmds.push_back(CmdFunctionMapper(cmd, pf));
}