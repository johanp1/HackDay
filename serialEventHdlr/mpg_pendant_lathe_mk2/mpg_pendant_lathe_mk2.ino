#include "button.h"
#include "joystick.h"
#include "sender.h"
#include "event_listner.h"
#include "buffer.h"
#include "selector.h"
#include "event_parser.h"
#include "receiver.h"
#include "mpg_pendant_lathe_mk2.h"
#include <avr/wdt.h>
#include <EEPROM.h>

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

template<typename F, typename O, typename D>
class CalibEventHandler : public EventFunctor
{
  public:
    CalibEventHandler(String const &event_name, F f, O* o, D &d) : EventFunctor{event_name}, f_(f), o_(o), d_(d){};

    void operator()(String& parsed_data)
    {
      f_(parsed_data, o_, d_);
    };
    
    O* o_;
    D& d_;
    F f_;
};

static void readCalibDataFromEEPROM();
static void calibrateWrapper(String& str, Joystick* j);
static void calibrateWrapper(String& str, Joystick* j, JoystickCalibData& d);
static void flipWrapper(String& str, Joystick* j);
static void flipWrapper(String& str, Joystick* j, JoystickCalibData& d);
static void resetWrapper();

static Sender sender;
static EventGenerator* event_generators[kNbrOfEventGenerators];
static Receiver receiver(String("rec"));
static EventParser eventParser;
static Joystick* x_joystick;
static Joystick* z_joystick;

static unsigned long heartbeatTimer = kHeartbeatPeriod;

static CalibData calibData;

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

  readCalibDataFromEEPROM();
  x_joystick = new Joystick("x", kJoystickXPin, calibData.x.flipped, calibData.x.low, calibData.x.mid, calibData.x.hi);
  z_joystick = new Joystick("z", kJoystickZPin, calibData.z.flipped, calibData.z.low, calibData.z.mid, calibData.z.hi);

  event_generators[6] = x_joystick;
  event_generators[6]->addEventListner(&sender);

  event_generators[7] = z_joystick;
  event_generators[7]->addEventListner(&sender);

  receiver.addEventListner(&eventParser);

  //eventParser.AddAcceptedHandler(*(new EventHandler<void (&)(String&, Joystick*), Joystick>(String{"calx"}, calibrateWrapper, x_joystick)));
  //eventParser.AddAcceptedHandler(*(new EventHandler<void (&)(String&, Joystick*), Joystick>(String{"calz"}, calibrateWrapper, z_joystick)));
  //eventParser.AddAcceptedHandler(*(new EventHandler<void (&)(String&, Joystick*), Joystick>(String{"flipx"}, flipWrapper, x_joystick)));
  //eventParser.AddAcceptedHandler(*(new EventHandler<void (&)(String&, Joystick*), Joystick>(String{"flipz"}, flipWrapper, z_joystick)));
  eventParser.AddAcceptedHandler(*(new ResetEventFunctor(String{"rst"})));
  eventParser.AddAcceptedHandler(*(new CalibEventHandler<void (&)(String&, Joystick*, JoystickCalibData&), Joystick, JoystickCalibData&>(String{"calx"}, calibrateWrapper, x_joystick, calibData.x)));
  eventParser.AddAcceptedHandler(*(new CalibEventHandler<void (&)(String&, Joystick*, JoystickCalibData&), Joystick, JoystickCalibData&>(String{"calz"}, calibrateWrapper, z_joystick, calibData.z)));
  eventParser.AddAcceptedHandler(*(new CalibEventHandler<void (&)(String&, Joystick*, JoystickCalibData&), Joystick, JoystickCalibData&>(String{"flipx"}, flipWrapper, x_joystick, calibData.x)));
  eventParser.AddAcceptedHandler(*(new CalibEventHandler<void (&)(String&, Joystick*, JoystickCalibData&), Joystick, JoystickCalibData&>(String{"flipz"}, flipWrapper, z_joystick, calibData.z)));
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

static void readCalibDataFromEEPROM()
{
  EEPROM.get(0, calibData);

  if (calibData.x.low & 0xffff == 0xffff)
  {
    // not calibrated
    calibData.x.low = 0;
    calibData.x.mid = 512;
    calibData.x.hi = 1023;
    calibData.x.flipped = false;
  }
  if (calibData.z.low & 0xffff == 0xffff)
  {
    // not calibrated
    calibData.z.low = 0;
    calibData.z.mid = 512;
    calibData.z.hi = 1023;
    calibData.z.flipped = false;
  }
  EEPROM.put(0, calibData);
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

static void calibrateWrapper(String& str, Joystick* j, JoystickCalibData& d)
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
  // do something with d...
}

static void flipWrapper(String& str, Joystick* j)
{
  bool flipped = str.toInt() > 0 ? true : false; 
  j->SetFlipped(flipped);
}

static void flipWrapper(String& str, Joystick* j, JoystickCalibData& d)
{
  bool flipped = str.toInt() > 0 ? true : false; 
  j->SetFlipped(flipped);

  //store the joystick::flipped
  d.flipped = flipped;
  EEPROM.put(0, calibData);
}


static void resetWrapper()
{
  wdt_enable(WDTO_15MS);
}