#include "event_parser.h"
#include "Arduino.h"

EventParser::EventParser()
{
   nbrOfAcceptedHandlers_ = 0;
}

void EventParser::HandleEvent(C_Event& e)
{
   ParseEvent(e);
}
void EventParser::ParseEvent(C_Event& e)
{
   int i = 0;
   EventFunctor *hdlr = nullptr;

   // fetch command
   while((hdlr == nullptr) && (i < nbrOfAcceptedHandlers_))
   {
      if (e.GetName().compareTo(eventHandlers_[i]->event_name_) == 0) //data starts with a command
      {
         hdlr = eventHandlers_[i]; // found handlerfor this command
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

void EventParser::AddAcceptedHandler(EventFunctor &h)
{
   if (nbrOfAcceptedHandlers_ < c_maxNbrOfAcceptedHandlers)
   {
      eventHandlers_[nbrOfAcceptedHandlers_] = &h;
      nbrOfAcceptedHandlers_++;
   }   
}

int EventParser::GetNbrOfAcceptedHandlers()
{
   return nbrOfAcceptedHandlers_;
}