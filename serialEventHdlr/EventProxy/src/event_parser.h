#ifndef __C_EVENT_PARSER_H__
#define __C_EVENT_PARSER_H__

#include "event_listner.h"

constexpr byte c_maxNbrOfAcceptedCmds = 8;

class CommandHandler
{
public:
   CommandHandler(String const &cmd_) : cmd(cmd_){};
   virtual void operator()(String &_parsedData) { (void)_parsedData; };
   virtual void operator()(){};

//private:
   String cmd;
};

class EventParser : public EventListner
{
public:
   EventParser(void);

   void HandleEvent(C_Event &e);

   void AddAcceptedCmd(CommandHandler &f);

   int GetNbrOfAcceptedCmds();

private:
   void ParseEvent(String &data);

   //String acceptedCmds[c_maxNbrOfAcceptedCmds];
   CommandHandler *commandHandlers[c_maxNbrOfAcceptedCmds];
   int nbrOfAcceptedCmds;
};

#endif // __C_EVENT_PARSER_H__