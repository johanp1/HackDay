#ifndef __C_EVENT_PARSER_H__
#define __C_EVENT_PARSER_H__

#define MAX_NBR_OF_ACCEPTED_CMDS 8

#include "event_listner.h"

class ParserFunctionoid
{
   public:
   virtual void execute(String& _parsedData) = 0;
};

class CmdFunctionMapper
{
   public:
   CmdFunctionMapper() {pf = NULL;};
   CmdFunctionMapper(String& _cmd, ParserFunctionoid* _pf) : cmd(_cmd), pf(_pf) {};
   void execute(String& _parsedData);

   String cmd;

   private:
   ParserFunctionoid* pf;
};

class EventParser : public EventListner
{
   public:
   EventParser(void);

   void handleEvent(C_Event& e);
   void addAcceptedCmd(String& cmd, ParserFunctionoid& pf);
   int getNbrOfAcceptedCmds();

   private:
   void parseEvent(String& data);
   
   CmdFunctionMapper acceptedCmds[MAX_NBR_OF_ACCEPTED_CMDS];
   int nbrOfAcceptedCmds;
};

#endif // __C_EVENT_PARSER_H__