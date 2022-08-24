#include "button.h"
#include "sender.h"
#include "event_listner.h"
#include "buffer.h"
#include "selector2.h"
#include "event_parser.h"
#include "receiver.h"
#include "mpg_pendant_lathe.h"
#include "lcd_writer.h"
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>

constexpr auto cNbrOfEventGenerators = cNbrOfButtons + cNbrOfSelectors;
constexpr auto cHeartbeatPeriod = 2000; //2000ms

class UpdateXCommandHandler : public EventFunctor
{
  public:
    UpdateXCommandHandler(Model& model) : EventFunctor{String("xpos")}, model_(model) {};

    void operator()(String& _parsedData)
    {
      model_.SetX(_parsedData.toFloat());
    };

  private:
    Model& model_;
};

class UpdateYCommandHandler : public EventFunctor
{
  public:
    UpdateYCommandHandler(Model& model) : EventFunctor{String("ypos")}, model_(model) {};

    void operator()(String& _parsedData)
    {
      model_.SetY(_parsedData.toFloat());
    };

  private:
    Model& model_;
};

class UpdateSpindleSpeedCommandHandler : public EventFunctor
{
  public:
    UpdateSpindleSpeedCommandHandler(Model& model) : EventFunctor{String("ss")}, model_(model) {};

    void operator()(String& _parsedData)
    {
      model_.SetSpindleSpeed(_parsedData.toFloat());
    };

  private:
    Model& model_;
};

class AxisViewCommandHandler : public EventFunctor
{
  public:
    AxisViewCommandHandler(LcdView<LiquidCrystal_PCF8574>& view) : EventFunctor{String("sela")}, view_(view) {};

    void operator()(String& _parsedData)
    {
      if((_parsedData.toInt() == 1) || (_parsedData.toInt() == 2))
      {
        view_.SetEnabled(true);
      }
      else
      {
        view_.SetEnabled(false);
      }
    };

  private:
    LcdView<LiquidCrystal_PCF8574>& view_;
};

class SpindleViewCommandHandler : public EventFunctor
{
  public:
    SpindleViewCommandHandler(LcdView<LiquidCrystal_PCF8574>& view) : EventFunctor{String("sela")}, view_(view) {};

    void operator()(String& _parsedData)
    {
      if(_parsedData.toInt() == 3)
      {
        view_.SetEnabled(true);
      }
      else
      {
        view_.SetEnabled(false);
      }
    };

  private:
    LcdView<LiquidCrystal_PCF8574>& view_;
};

class ActiveAxisCommandHandler : public EventFunctor
{
  public:
    ActiveAxisCommandHandler(Model& model) : EventFunctor{String("sela")}, model_(model) {};

    void operator()(String& _parsedData)
    {
      if(_parsedData.toInt() == 1)
      {
        model_.SetActiveAxis(axis_x);
      }
      if(_parsedData.toInt() == 2)
      {
        model_.SetActiveAxis(axis_y);
      }
    };

  private:
    Model& model_;
};

static LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27
Model lcdModel;
static Sender sender;
static EventGenerator* eventGenerators[cNbrOfEventGenerators];
static Receiver receiver(String("rec"));

static unsigned long heartbeatTimer = cHeartbeatPeriod;

void setup() {
  AxisView<LiquidCrystal_PCF8574>* axisView = new AxisView<LiquidCrystal_PCF8574>(lcd, lcdModel);
  SpindleView<LiquidCrystal_PCF8574>* spindleView =new SpindleView<LiquidCrystal_PCF8574>(lcd, lcdModel);

  UpdateXCommandHandler* updateXCommandHandler = new UpdateXCommandHandler(lcdModel);
  UpdateYCommandHandler* updateYCommandHandler = new UpdateYCommandHandler(lcdModel);
  UpdateSpindleSpeedCommandHandler* updateSpindleCommandHandler = new UpdateSpindleSpeedCommandHandler(lcdModel);
  AxisViewCommandHandler* axisViewCommandHandler = new AxisViewCommandHandler(*axisView);
  SpindleViewCommandHandler* spindleViewCommandHandler = new SpindleViewCommandHandler(*spindleView);
  ActiveAxisCommandHandler* activeAxisCommandHandler = new ActiveAxisCommandHandler(lcdModel);
  
  Serial.begin(38400);
  Serial.setTimeout(500);
  Serial.println("mpgPendant::setup()");

  // initialize the lcd
  lcd.begin(16, 2); 
  lcd.clear();
  lcd.setBacklight(200);

  eventGenerators[0] = new Button("func", cFuncButtonPin, cButtonDebounceDelay);
  eventGenerators[0]->addEventListner(&sender);

  eventGenerators[1] = new Button("jpos", cJogNegButtonPin, cButtonDebounceDelay);
  eventGenerators[1]->addEventListner(&sender);

  eventGenerators[2] = new Button("jneg", cJogPosButtonPin, cButtonDebounceDelay);
  eventGenerators[2]->addEventListner(&sender);

  eventGenerators[3] = new Button("est", cEStopButtonPin, cButtonDebounceDelay);
  eventGenerators[3]->addEventListner(&sender);

  eventGenerators[4] = new Selector2("sela", cAxisSelectorPin1, cAxisSelectorPin2, cAxisSelectorPin3, cSelectorDebounceDelay);
  eventGenerators[4]->addEventListner(&sender);

  // register selector changes to the view's event handlers
  eventGenerators[4]->addEventListner(axisView->GetController());
  eventGenerators[4]->addEventListner(spindleView->GetController());
  
  //  eventGenerators[5] = new Selector("sels", cScaleSelectorPin, cSelectorDebounceDelay);
  //  eventGenerators[5]->addEventListner(&sender);

  // register serial events the view's event handlers
  receiver.addEventListner(axisView->GetController());
  receiver.addEventListner(spindleView->GetController());

  axisView->GetController()->AddAcceptedHandler(*updateXCommandHandler);
  axisView->GetController()->AddAcceptedHandler(*updateYCommandHandler);
  spindleView->GetController()->AddAcceptedHandler(*updateSpindleCommandHandler);

  axisView->GetController()->AddAcceptedHandler(*axisViewCommandHandler);
  spindleView->GetController()->AddAcceptedHandler(*spindleViewCommandHandler);

  axisView->GetController()->AddAcceptedHandler(*activeAxisCommandHandler);
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
  //eventGenerators[5]->scan();

  //send heart-beat every <cHeartbeatPeriod> [ms]
  if (millis() > heartbeatTimer)
  {
    String tmpStr = "hb";
    C_Event hb_ev = C_Event(tmpStr, "");
    sender.HandleEvent(hb_ev);
    heartbeatTimer = millis() + cHeartbeatPeriod;
  }

  delay(10); // waits 10ms
}

void serialEvent()
{
  receiver.scan();
}
