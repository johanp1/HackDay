#ifndef __C_EVENT_PARSER_H__
#define __C_EVENT_PARSER_H__

#include "event_listner.h"

constexpr byte c_maxNbrOfAcceptedCmds = 8;

class ParserFunctionoid
{
   public:
   ParserFunctionoid(String const& cmd_) : cmd(cmd_){};
   virtual void execute(String& _parsedData) {_parsedData = _parsedData;};

   String cmd;   
};

class EventParser : public EventListner
{
   public:
   EventParser(void);

   void HandleEvent(C_Event& e);
   void AddAcceptedCmd(ParserFunctionoid& pf);
   int GetNbrOfAcceptedCmds();

   private:
   void ParseEvent(String& data);
   
   ParserFunctionoid* acceptedCmds[c_maxNbrOfAcceptedCmds];
   int nbrOfCmds;
};

#endif // __C_EVENT_PARSER_H__