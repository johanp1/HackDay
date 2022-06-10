#include "event_parser.h"
#include "Arduino.h"

EventParser::EventParser()
{
   nbrOfAcceptedCmds = 0;
}

void EventParser::HandleEvent(C_Event& e)
{
   ParseEvent(e);
}
void EventParser::ParseEvent(C_Event& e)
{
   int i = 0;
   CommandHandler *hdlr = nullptr;

   // fetch command
   while((hdlr == nullptr) && (i < nbrOfAcceptedCmds))
   {
      if (e.GetName().compareTo(commandHandlers[i]->cmd) == 0) //data starts with a command
      {
         hdlr = commandHandlers[i]; // found handlerfor this command
      }

      i++;
   }

   if(hdlr != nullptr)
   {
      String event_data = e.GetData();
      if (event_data.compareTo("") == 0)
      {
         (*hdlr)();
      }
      else
      {
         (*hdlr)(event_data);
      }
   }
}

void EventParser::AddAcceptedCmd(CommandHandler &f)
{
   if (nbrOfAcceptedCmds < c_maxNbrOfAcceptedCmds)
   {
      commandHandlers[nbrOfAcceptedCmds] = &f;
      nbrOfAcceptedCmds++;
   }   
}

int EventParser::GetNbrOfAcceptedCmds()
{
   return nbrOfAcceptedCmds;
}