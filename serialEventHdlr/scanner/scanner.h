#ifndef __C_SCANNER_H__
#define __C_SCANNER_H__

#include "event_parser.h"
#include "src/step_gen.h"
#include "src/axis_ctrl.h"
#include "src/scanner_ctrl.h"

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

class JogHandler
{
  public:
  JogHandler(AxisCtrl& a, String& name) : axisCtrl_(a), name_(name)
  {
    jogDoneObserver_ = new StepObserverHandler<JogHandler, void (&)(JogHandler* h)>(this, JogDoneHandler); 
  };

  static void JogStartHandler(String& str, JogHandler* h)
  {
    h->JogStartHandlerInternal(str);
  };

  void JogStartHandlerInternal(String& str)
  {
    //attach observer to be called when jog completed
    axisCtrl_.GetStepGen().AttachDoneObserver(jogDoneObserver_);

    auto pos = str.toFloat();  
    axisCtrl_.MoveToRelativePosition(pos);
  };

  static void JogDoneHandler(JogHandler* h) {h->JogDoneHandlerInternal();};

  void JogDoneHandlerInternal()
  {
    axisCtrl_.GetStepGen().DetachDoneObserver();

    //String sendStr{str};
    String sendStr{name_};
    sendStr.concat("_");
    sendStr.concat(axisCtrl_.GetPosition());
    cli();  // serial.send seems to be upset by interrupts...
    Serial.println(sendStr);
    sei();
  };

  private:
  StepObserverHandler<JogHandler, void (&)(JogHandler*)>* jogDoneObserver_;
  AxisCtrl& axisCtrl_;
  const String name_;
};

#endif //__C_SCANNER_H__