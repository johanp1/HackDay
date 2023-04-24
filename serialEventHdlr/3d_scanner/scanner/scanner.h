#ifndef __C_SCANNER_H__
#define __C_SCANNER_H__

#include "event_generator.h"
#include "event_parser.h"
#include "step_gen.h"

template<typename F>
class DirectionEventHandler : public EventFunctor
{
  public:
    DirectionEventHandler(String const &event_name, F f) : EventFunctor{event_name}, f_(f) {};

    void operator()(String& _parsedData)
    {
      f_(_parsedData);
    };

    F f_;
};

template<typename F, typename O>
class EventHandler : public EventFunctor
{
  public:
    EventHandler(String const &event_name, F f, O* o) : EventFunctor{event_name}, f_(f), o_(o) {};

    void operator()(String& _parsedData)
    {
      f_(_parsedData, o_);
    };

    F f_;
    O* o_;
};

#endif //__C_SCANNER_H__