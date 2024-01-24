#include "button.h"
#include "joystick.h"
#include "sender.h"
#include "event_listner.h"
#include "buffer.h"
#include "selector.h"
#include "event_parser.h"
#include "receiver.h"
#include "mpg_pendant_lathe.h"
#include "lcd_writer.h"
#include <LiquidCrystal_PCF8574.h>

constexpr auto kNbrOfEventGenerators = kNbrOfButtons + kNbrOfSelectors + 2;

template<typename F, typename O>
class ControllerEventHandler : public EventFunctor
{
  public:
    ControllerEventHandler(String const &event_name, F f, O* o) : EventFunctor{event_name}, f_(f), o_(o) {};

    void operator()(String& parsed_data)
    {
      f_(parsed_data, o_);
    };
    
    O* o_;
    F f_;
};

static void setSpindleSpeedWrapper(String& s, Controller<LiquidCrystal_PCF8574>* c);
static void enableSpindleViewWrapper(String& s, Controller<LiquidCrystal_PCF8574>* c);
static void setXPosWrapper(String& s, Controller<LiquidCrystal_PCF8574>* c);
static void setZPosWrapper(String& s, Controller<LiquidCrystal_PCF8574>* c);
static void enableAxisViewWrapper(String& s, Controller<LiquidCrystal_PCF8574>* c);

LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27
Model lcdModel;
static Sender sender;
static EventGenerator* eventGenerators[kNbrOfEventGenerators];
static Receiver receiver(String("rec"));

static unsigned long heartbeatTimer = kHeartbeatPeriod;

void setup() {  
  AxisView<LiquidCrystal_PCF8574>* axisView = new AxisView<LiquidCrystal_PCF8574>(lcd, lcdModel);
  SpindleView<LiquidCrystal_PCF8574>* spindleView =new SpindleView<LiquidCrystal_PCF8574>(lcd, lcdModel);

  Serial.begin(38400);
  Serial.setTimeout(500);
  Serial.println("mpgPendant::setup()");

  // initialize the lcd
  lcd.begin(16, 2); 
  lcd.clear();
  lcd.setBacklight(200);

  eventGenerators[0] = new Button("func", kFuncButtonPin, kButtonDebounceDelay);
  eventGenerators[0]->addEventListner(&sender);

  eventGenerators[1] = new Button("jpos", kJogPosButtonPin, kButtonDebounceDelay);
  eventGenerators[1]->addEventListner(&sender);

  eventGenerators[2] = new Button("jneg", kJogNegButtonPin, kButtonDebounceDelay);
  eventGenerators[2]->addEventListner(&sender);

  eventGenerators[3] = new Button("est", kEStopButtonPin, kButtonDebounceDelay);
  eventGenerators[3]->addEventListner(&sender);

  eventGenerators[4] = new Selector("sela", kAxisSelectorPin, kSelectorDebounceDelay, kSelectorStateVolts, kNbrOfSelectorStates, kSelectorStateValueUncertainty);
  eventGenerators[4]->addEventListner(&sender);

  // register selector changes to the view's event handlers
  eventGenerators[4]->addEventListner(axisView->GetController());
  eventGenerators[4]->addEventListner(spindleView->GetController());
  
  eventGenerators[5] = new Selector("sels", cScaleSelectorPin, kSelectorDebounceDelay, kSelectorStateVolts, kNbrOfSelectorStates, kSelectorStateValueUncertainty);
  eventGenerators[5]->addEventListner(&sender);

  Joystick* x_joystick = new Joystick("x", kJoystickXPin);
  eventGenerators[6] = x_joystick;
  eventGenerators[6]->addEventListner(&sender);

  Joystick* z_joystick = new Joystick("z", kJoystickZPin);
  eventGenerators[7] = z_joystick;
  eventGenerators[7]->addEventListner(&sender);

  // register serial events the view's event handlers
  receiver.addEventListner(axisView->GetController());
  receiver.addEventListner(spindleView->GetController());

  axisView->GetController()->AddAcceptedHandler(*(new ControllerEventHandler<void (&)(String&, Controller<LiquidCrystal_PCF8574>*), Controller<LiquidCrystal_PCF8574>>(String{"xpos"}, setXPosWrapper, axisView->GetController())));
  axisView->GetController()->AddAcceptedHandler(*(new ControllerEventHandler<void (&)(String&, Controller<LiquidCrystal_PCF8574>*), Controller<LiquidCrystal_PCF8574>>(String{"zpos"}, setZPosWrapper, axisView->GetController())));
  spindleView->GetController()->AddAcceptedHandler(*(new ControllerEventHandler<void (&)(String&, Controller<LiquidCrystal_PCF8574>*), Controller<LiquidCrystal_PCF8574>>(String{"ss"}, setSpindleSpeedWrapper, spindleView->GetController())));

  axisView->GetController()->AddAcceptedHandler(*(new ControllerEventHandler<void (&)(String&, Controller<LiquidCrystal_PCF8574>*), Controller<LiquidCrystal_PCF8574>>(String{"sela"}, enableAxisViewWrapper, axisView->GetController())));
  spindleView->GetController()->AddAcceptedHandler(*(new ControllerEventHandler<void (&)(String&, Controller<LiquidCrystal_PCF8574>*), Controller<LiquidCrystal_PCF8574>>(String{"sela"}, enableSpindleViewWrapper, spindleView->GetController())));

  x_joystick->Calibrate();
  z_joystick->Calibrate();
}

void loop() {

  byte i;
  C_Event e;
  byte dummy = 0;
  
  eventGenerators[0]->scan();
  eventGenerators[1]->scan();
  eventGenerators[2]->scan();
  eventGenerators[3]->scan();
  eventGenerators[4]->scan();
  eventGenerators[5]->scan();
  eventGenerators[6]->scan();
  eventGenerators[7]->scan();

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

static void setSpindleSpeedWrapper(String& s, Controller<LiquidCrystal_PCF8574>* c)
{
  c->model_->SetSpindleSpeed(s.toInt());
}

static void enableSpindleViewWrapper(String& s, Controller<LiquidCrystal_PCF8574>* c)
{
  if (s.toInt() == 2)
  {
    c->view_->SetEnabled(true);
  }
  else 
  {
    c->view_->SetEnabled(false);
  }
}

static void enableAxisViewWrapper(String& s, Controller<LiquidCrystal_PCF8574>* c)
{
  if (s.toInt() == axis_x)
  {
    c->view_->SetEnabled(true);
    c->model_->SetActiveAxis(axis_x);
  }
  else if (s.toInt() == axis_z)
  {
    c->view_->SetEnabled(true);
    c->model_->SetActiveAxis(axis_z);
  }
  else
  {
    c->view_->SetEnabled(false);
  }
}

static void setXPosWrapper(String& s, Controller<LiquidCrystal_PCF8574>* c)
{
  c->model_->SetX(s.toFloat());
}

static void setZPosWrapper(String& s, Controller<LiquidCrystal_PCF8574>* c)
{
  c->model_->SetZ(s.toFloat());
}
