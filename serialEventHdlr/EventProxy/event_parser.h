#ifndef __C_EVENT_PARSER_H__
#define __C_EVENT_PARSER_H__

#include "event_listner.h"
#include <vector>

class ParserFunctionoid
{
   public:
   virtual void execute(String& _parsedData) = 0;
};

class CmdFunctionMapper
{
   public:
   CmdFunctionMapper(String& _cmd, ParserFunctionoid& _pf) : cmd(_cmd), pf(_pf) {};
   void execute(String& _parsedData);

   String cmd;

   private:
   ParserFunctionoid& pf;
};

class EventParser : public EventListner
{
   public:
   EventParser(void);

   void handleEvent(C_Event& e);
   void addAcceptedCmd(String& cmd, ParserFunctionoid& pf);

   private:
   void parseEvent(String& data);
   
   vector<CmdFunctionMapper> acceptedCmds;
};

#endif // __C_EVENT_PARSER_H__