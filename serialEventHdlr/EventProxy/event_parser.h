#ifndef __C_EVENT_PARSER_H__
#define __C_EVENT_PARSER_H__

#include "event_listner.h"

class ParserFunctionoid
{
   public:
   virtual void executeCmd(void) = 0;
};


class EventParser : public EventListner
{
   public:
   EventParser(void);

   void handleEvent(C_Event& e);
   void addAcceptedCmd(String& cmdT, ParserFunctionoid& f);

   String cmdType;
   int cmdVal;
};

#endif // __C_EVENT_PARSER_H__