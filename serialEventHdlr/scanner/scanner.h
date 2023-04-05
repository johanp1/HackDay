#ifndef __C_SCANNER_H__
#define __C_SCANNER_H__

#include "event_generator.h"
#include "event_parser.h"
#include "step_gen.h"


/*
class SetPulsPerSecCommandHandler : public EventFunctor
{
  public:
    SetPulsPerSecCommandHandler(StepGen const &s, String const &event_name) : EventFunctor{event_name}, stepGen_(s) {};

    void operator()(String& _parsedData)
    {
      stepGen_.SetStepsPerSec(_parsedData.toInt());
    };

  private:
    StepGen const &stepGen_;
};

class SetRampingCommandHandler : public EventFunctor
{
  public:
    SetRampingCommandHandler(StepGen const &s, String const &event_name) : EventFunctor{event_name}, stepGen_{s} {};

    void operator()(String& _parsedData)
    {
      stepGen_.SetUseRamping(_parsedData.toInt());
    };

  private:
    StepGen const &stepGen_;
};
*/
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