#include "button.h"
#include "sender.h"
#include "event_listner.h"
#include "buffer.h"
#include "selector2.h"
#include "event_parser.h"
#include "receiver.h"
#include "mpg_pendant_lathe.h"
#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>

constexpr auto cNbrOfEventGenerators = cNbrOfButtons + cNbrOfSelectors;
constexpr auto cHeartbeatPeriod = 2000; //2000ms

class UpdateXCommandHandler : public CommandHandler
{
   public:
   UpdateXCommandHandler(LiquidCrystal_PCF8574& lcd_) : CommandHandler{String("x")}, lcd(lcd_) {}; 

   void operator()(String& _parsedData)
   {
      lcd.setCursor(0, 0);
      lcd.print("*** first line.");
   };

   private:
   LiquidCrystal_PCF8574& lcd;
};

class UpdateYCommandHandler : public CommandHandler
{
   public:
   UpdateYCommandHandler(LiquidCrystal_PCF8574& lcd_) : CommandHandler{String("y")}, lcd(lcd_) {}; 

   void operator()(String& _parsedData)
   {
      lcd.setCursor(1, 0);
      lcd.print("*** sec line.");
   };

   private:
   LiquidCrystal_PCF8574& lcd;
};

static LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27
static Sender sender;
static EventGenerator* eventGenerators[cNbrOfEventGenerators];
static Receiver receiver(String("rec"));
static EventParser ep;
static UpdateXCommandHandler updateXCommandHandler(lcd);
static UpdateYCommandHandler updateYCommandHandler(lcd);
static unsigned long heartbeatTimer = cHeartbeatPeriod;

void setup() {
  Serial.begin(38400);
  Serial.setTimeout(500);
  Serial.println("mpgPendant::setup()");

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

//  eventGenerators[5] = new Selector("sels", cScaleSelectorPin, cSelectorDebounceDelay);
//  eventGenerators[5]->addEventListner(&sender);

//  receiver.addEventListner(&ep);
//  ep.AddAcceptedCmd(updateXCommandHandler);
//  ep.AddAcceptedCmd(updateYCommandHandler);

  lcd.begin(16, 2); // initialize the lcd
  lcd.clear();
  lcd.setBacklight(255);
  lcd.print("hej");
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
