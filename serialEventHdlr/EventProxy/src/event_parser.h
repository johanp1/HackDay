#ifndef __C_EVENT_PARSER_H__
#define __C_EVENT_PARSER_H__

#include "event_listner.h"

constexpr byte c_maxNbrOfAcceptedHandlers = 12;

class EventFunctor
{
public:
   EventFunctor(String const &event_name) : event_name_(event_name){};
   virtual void operator()(String &_parsedData) { (void)_parsedData; };
   virtual void operator()(){};

//private:
   String event_name_;
};

class EventParser : public EventListner
{
public:
   EventParser(void);

   void HandleEvent(C_Event &e);

   void AddAcceptedHandler(EventFunctor &h);

   int GetNbrOfAcceptedHandlers();

private:
   void ParseEvent(C_Event& e);

   EventFunctor *eventHandlers_[c_maxNbrOfAcceptedHandlers];
   int nbrOfAcceptedHandlers_;
};

#endif // __C_EVENT_PARSER_H__