#include "event_parser.h"
#include "Arduino.h"

EventParser::EventParser(void)
{
   cmdType = "";
   cmdVal = 0;
}

void EventParser::handleEvent(C_Event& e)
{
   String ev;
   //serializedData.push_back(e.serializeData());
   ev = e.serialize();
   cmdType = "apa";
   cmdVal = 123;
}

void EventParser::addAcceptedCmd(String& cmdT, ParserFunctionoid& f)
{
   if(cmdT.compare("apa") == 0)
   {
      f.executeCmd();
   }
}