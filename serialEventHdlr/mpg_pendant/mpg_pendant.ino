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
static EventGenerator* evGenList[kNbrOfEventGenerators];
static unsigned long heartbeatTimer = kHeartbeatPeriod;

void setup() {
   Serial.begin(38400);  // opens serial port, sets data rate to 9600 bps
   Serial.setTimeout(500);
   Serial.println("mpgPendant::setup()");
   
   evGenList[0] = new Button("rth", kFuncButtonPin, kButtonDebounceDelay);
   evGenList[0]->addEventListner(&sender);

   evGenList[1] = new Button("run", kRunButtonPin, kButtonDebounceDelay);
   evGenList[1]->addEventListner(&sender);

   evGenList[2] = new Button("est", kEStopButtonPin, kButtonDebounceDelay); 
   evGenList[2]->addEventListner(&sender);

   evGenList[3] = new Selector("sela", kAxisSelectorPin, kSelectorDebounceDelay);
   evGenList[3]->addEventListner(&sender);
   
   evGenList[4] = new Selector("sels", kScaleSelectorPin, kSelectorDebounceDelay);
   evGenList[4]->addEventListner(&sender);

   evGenList[5] = new RotaryEncoder("jog", kEncoderClockPin, kEncoderDirectionPin);
   evGenList[5]->addEventListner(&buffer);
   isrFunct.addEventGenerator(evGenList[5]);
   attachInterrupt(digitalPinToInterrupt(kEncoderClockPin), myISR, RISING);
}

void loop() {  

   byte i;
   C_Event e;

   evGenList[0]->scan();
   evGenList[1]->scan();
   evGenList[2]->scan();
   evGenList[3]->scan();
   evGenList[4]->scan();
   // we don't need to "evGenList[5]->scan();" since it is connected to an interrupt instead.
   // Also the implementation of RotaryEncoder::scan() currently only works for interrupts. If it is pulled 
   // continously it will update its position every iteration
   
   while(buffer.get(e))
   {  
      sender.handleEvent(e);
   }

   //send heart-beat every <kHeartbeatPeriod> [ms]
   if(millis() > heartbeatTimer)
   {
      String tmpStr = "hb";
      C_Event hb_ev = C_Event(tmpStr, 1);
      sender.handleEvent(hb_ev);
      heartbeatTimer = millis() + kHeartbeatPeriod;
   }

   delay(10); // waits 10ms
}

static void myISR(void)
{
   isrFunct.execute();
}
