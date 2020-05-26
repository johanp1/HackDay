#include "event_parser.h"
#include "Arduino.h"

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
         int idx = unparsedData.indexOf(acceptedCmds.at(i).cmd);

         if (idx == 0) //data starts with a command
         {
            String data;
            if (unparsedData.length() >= acceptedCmds.at(i).cmd.length())
            {
               data = unparsedData.substring(acceptedCmds.at(i).cmd.length());
            }
            acceptedCmds.at(idx).execute(data);
         }
      }
   }
}

void EventParser::addAcceptedCmd(String& cmd, ParserFunctionoid& pf)
{
   acceptedCmds.push_back(CmdFunctionMapper(cmd, pf));
}