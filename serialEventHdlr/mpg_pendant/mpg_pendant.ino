#include "button.h"
#include "encoder.h"
#include "sender.h"
#include "event_listner.h"
#include "buffer.h"
#include "selector.h"
#include "mpg_pendant.h"

constexpr auto kNbrOfEventGenerators = kNbrOfButtons + kNbrOfSelectors + 1/*kNbrOfRotaryEncoders*/;
constexpr auto kHeartbeatPeriod = 2000; //2000ms

static void myISR(void);

static IsrFunctionoid isrFunct;
static Sender sender;
static Buffer buffer;
static EventGenerator* eventGenerators[kNbrOfEventGenerators];
static unsigned long heartbeatTimer = kHeartbeatPeriod;

void setup() {
   Serial.begin(38400);  // opens serial port, sets data rate to 9600 bps
   Serial.setTimeout(500);
   Serial.println("mpgPendant::setup()");
   
   eventGenerators[0] = new Button("func", kFuncButtonPin, kButtonDebounceDelay);
   eventGenerators[0]->addEventListner(&sender);

   eventGenerators[1] = new Button("run", kRunButtonPin, kButtonDebounceDelay);
   eventGenerators[1]->addEventListner(&sender);

   eventGenerators[2] = new Button("est", kEStopButtonPin, kButtonDebounceDelay); 
   eventGenerators[2]->addEventListner(&sender);

   eventGenerators[3] = new Selector("sela", kAxisSelectorPin, kSelectorDebounceDelay);
   eventGenerators[3]->addEventListner(&sender);
   
   eventGenerators[4] = new Selector("sels", kScaleSelectorPin, kSelectorDebounceDelay);
   eventGenerators[4]->addEventListner(&sender);

   eventGenerators[5] = new RotaryEncoder("jog", kEncoderClockPin, kEncoderDirectionPin);
   eventGenerators[5]->addEventListner(&buffer);
   isrFunct.addEventGenerator(eventGenerators[5]);
   attachInterrupt(digitalPinToInterrupt(kEncoderClockPin), myISR, RISING);
}

void loop() {  

   byte i;
   C_Event e;

   eventGenerators[0]->scan();
   eventGenerators[1]->scan();
   eventGenerators[2]->scan();
   eventGenerators[3]->scan();
   eventGenerators[4]->scan();
   // we don't need to "eventGenerators[5]->scan();" since it is connected to an interrupt instead.
   // Also the implementation of RotaryEncoder::scan() currently only works for interrupts. If it is pulled 
   // continously it will update its position every iteration
   
   while(buffer.get(e))
   {  
      sender.HandleEvent(e);
   }

   //send heart-beat every <kHeartbeatPeriod> [ms]
   if(millis() > heartbeatTimer)
   {
      String tmpStr = "hb";
      C_Event hb_ev = C_Event(tmpStr, 1);
      sender.HandleEvent(hb_ev);
      heartbeatTimer = millis() + kHeartbeatPeriod;
   }

   delay(10); // waits 10ms
}

static void myISR(void)
{
   isrFunct.execute();
}
