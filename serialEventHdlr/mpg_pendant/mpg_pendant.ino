#include "button.h"
#include "encoder.h"
#include "sender.h"
#include "event_listner.h"
#include "buffer.h"
#include "selector.h"
#include "mpg_pendant.h"

#define NBR_OF_EVENT_GENERATORS NBR_OF_BUTTONS+NBR_OF_SELECTORS+1
#define HEARTBEAT_PERIOD 2000 //2000ms
static void encoderISR(void);

Button buttons[NBR_OF_BUTTONS] = {Button("rth", RTH_BUTTON_PIN, BUTTON_DEBOUNCE_DELAY),
								                  Button("run", RUN_BUTTON_PIN, BUTTON_DEBOUNCE_DELAY),
								                  Button("est", EST_BUTTON_PIN, BUTTON_DEBOUNCE_DELAY)} ;
RotaryEncoder encoder("jog", ENCODER_CLK_PIN, ENCODER_DT_PIN);
Selector selectors[NBR_OF_SELECTORS] = {Selector("sela", AXIS_SELECTOR_PIN, SELECTOR_DEBOUNCE_DELAY), 
									            	        Selector("sels", SCALE_SELECTOR_PIN, SELECTOR_DEBOUNCE_DELAY)};
Sender sender;
Buffer buffer;

EventGenerator* evGenList[NBR_OF_EVENT_GENERATORS];

unsigned long heartbeatTimer = HEARTBEAT_PERIOD;

void setup() {
   Serial.begin(38400);  // opens serial port, sets data rate to 9600 bps
   Serial.setTimeout(500);

   attachInterrupt(digitalPinToInterrupt(ENCODER_CLK_PIN), encoderISR, RISING);

   Serial.println("mpgPendant::setup()");

   buttons[0].addEventListner(&sender);
   buttons[1].addEventListner(&sender);
   buttons[2].addEventListner(&sender);
   selectors[0].addEventListner(&sender);
   selectors[1].addEventListner(&sender);
   encoder.addEventListner(&buffer);

   evGenList[0] = &buttons[0]; 
   evGenList[1] = &buttons[1];
   evGenList[2] = &buttons[2];
   evGenList[3] = &selectors[0];
   evGenList[4] = &selectors[1];
   evGenList[5] = &encoder;

}

void loop() {  

   byte i;
   C_Event e;
   
   for (i = 0; i<NBR_OF_EVENT_GENERATORS; i++)
   {
      evGenList[i]->scan();
   }

   while(buffer.get(e))
   {  
      sender.handleEvent(e);
   }

   //send heart-beat every second
   if(millis() > heartbeatTimer)
   {
      String tmpStr = "hb";
      C_Event hb_ev = C_Event(tmpStr, 1);
      sender.handleEvent(hb_ev);
      heartbeatTimer = millis() + HEARTBEAT_PERIOD;
   }

   delay(10); // waits 10ms
}

static void encoderISR(void)
{
   encoder.update();
}
