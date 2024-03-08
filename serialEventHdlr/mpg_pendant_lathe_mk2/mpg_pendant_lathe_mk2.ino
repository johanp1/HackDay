#include "button.h"
#include "joystick.h"
#include "sender.h"
#include "event_listner.h"
#include "buffer.h"
#include "selector.h"
#include "event_parser.h"
#include "receiver.h"
#include "mpg_pendant_lathe_mk2.h"

constexpr auto kNbrOfEventGenerators = kNbrOfButtons + kNbrOfSelectors + 2;

class ResetEventFunctor : public EventFunctor
{
public:
   ResetEventFunctor(String const &event_name) : EventFunctor(event_name){};
   void operator()(){setup();};
};

template<typename F, typename O>
class EventHandler : public EventFunctor
{
  public:
    EventHandler(String const &event_name, F f, O* o) : EventFunctor{event_name}, f_(f), o_(o) {};

    void operator()(String& parsed_data)
    {
      f_(parsed_data, o_);
    };
    
    O* o_;
    F f_;
};

static void calibrateWrapper(String& str, Joystick* j);

static Sender sender;
static EventGenerator* event_generators[kNbrOfEventGenerators];
static Receiver receiver(String("rec"));
static EventParser eventParser;
static Joystick* x_joystick = new Joystick("x", kJoystickXPin);
static Joystick* z_joystick = new Joystick("z", kJoystickZPin, 2*sizeof(int));

static unsigned long heartbeatTimer = kHeartbeatPeriod;

void setup() {  
  Serial.begin(38400);
  Serial.setTimeout(500);
  Serial.println("mpgPendant::setup()");

  event_generators[0] = new Button("func", kFuncButtonPin, kButtonDebounceDelay);
  event_generators[0]->addEventListner(&sender);

  event_generators[1] = new Button("jpos", kJogPosButtonPin, kButtonDebounceDelay);
  event_generators[1]->addEventListner(&sender);

  event_generators[2] = new Button("jneg", kJogNegButtonPin, kButtonDebounceDelay);
  event_generators[2]->addEventListner(&sender);

  event_generators[3] = new Button("est", kEStopButtonPin, kButtonDebounceDelay);
  event_generators[3]->addEventListner(&sender);

  event_generators[4] = new Selector("sela", kAxisSelectorPin, kSelectorDebounceDelay, kSelectorStateVolts, kNbrOfSelectorStates, kSelectorStateValueUncertainty);
  event_generators[4]->addEventListner(&sender);
  
  event_generators[5] = new Selector("sels", cScaleSelectorPin, kSelectorDebounceDelay, kSelectorStateVolts, kNbrOfSelectorStates, kSelectorStateValueUncertainty);
  event_generators[5]->addEventListner(&sender);

  event_generators[6] = x_joystick;
  event_generators[6]->addEventListner(&sender);

  event_generators[7] = z_joystick;
  event_generators[7]->addEventListner(&sender);

  receiver.addEventListner(&eventParser);

  eventParser.AddAcceptedHandler(*(new EventHandler<void (&)(String&, Joystick*), Joystick>(String{"calx"}, calibrateWrapper, x_joystick)));
  eventParser.AddAcceptedHandler(*(new EventHandler<void (&)(String&, Joystick*), Joystick>(String{"calz"}, calibrateWrapper, z_joystick)));
  eventParser.AddAcceptedHandler(*(new ResetEventFunctor(String{"rst"})));
}

void loop() {  
  event_generators[0]->scan();
  event_generators[1]->scan();
  event_generators[2]->scan();
  event_generators[3]->scan();
  event_generators[4]->scan();
  event_generators[5]->scan();
  event_generators[6]->scan();
  event_generators[7]->scan();

  //send heart-beat every <kHeartbeatPeriod> [ms]
  if (millis() > heartbeatTimer)
  {
    String tmpStr = "hb";
    C_Event hb_ev = C_Event(tmpStr, 1);
    sender.HandleEvent(hb_ev);
    heartbeatTimer = millis() + kHeartbeatPeriod;
  }

  delay(kLoopDelayTime);
}

void serialEvent()
{
  receiver.scan();
}

static void resetWrapper()
{
  setup();
}

static void calibrateWrapper(String& str, Joystick* j)
{
  if (str.compareTo("hi") == 0)
  {
    j->CalibrateHi();
  }
  if (str.compareTo("mid") == 0)
  {
    j->CalibrateMid();
  }
  if (str.compareTo("low") == 0)
  {
    j->CalibrateLow();
  }
}