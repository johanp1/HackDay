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
   for (i = 0; i < nbrOfAcceptedHandlers_; i++)
   {
      if(eventHandlers_[i] != nullptr)
      {
         if (e.GetName().compareTo(eventHandlers_[i]->event_name_) == 0) //data starts with a command
         {
            if ( e.GetData().compareTo("") == 0)
            {
               (*eventHandlers_[i])();
            }
            else
            {
               (*eventHandlers_[i])(e.GetData());
            }
         }
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