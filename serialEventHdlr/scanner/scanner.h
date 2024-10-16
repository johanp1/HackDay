#ifndef __C_SCANNER_H__
#define __C_SCANNER_H__

#include "event_parser.h"
#include "step_gen.h"

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

template<typename F, typename O>
class EventHandlerNoArg : public EventFunctor
{
  public:
    EventHandlerNoArg(String const &event_name, F f, O* o) : EventFunctor{event_name}, f_(f), o_(o) {};

    void operator()()
    {
      f_(o_);
    };

    F f_;
    O* o_;
};


template<typename F, typename O, typename D>
class EventHandlerExtendedArg : public EventFunctor
{
  public:
    EventHandlerExtendedArg(String const &event_name, F f, O* o, D &d) : EventFunctor{event_name}, f_(f), o_(o), d_(d){};

    void operator()(String& parsed_data)
    {
      f_(parsed_data, o_, d_);
    };
    
    O* o_;
    D& d_;
    F f_;
};

#endif //__C_SCANNER_H__