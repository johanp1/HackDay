#include "button.h"
#include "encoder.h"
#include "sender.h"
#include "event_listner.h"
#include "buffer.h"
#include "selector.h"
#include "mpg_pendant.h"

#define NBR_OF_EVENT_GENERATORS NBR_OF_BUTTONS+NBR_OF_SELECTORS+1

static void encoderISR(void);

C_Button buttons[NBR_OF_BUTTONS] = {C_Button("rth", RTH_BUTTON_PIN, BUTTON_DEBOUNCE_DELAY),
								                    C_Button("run", RUN_BUTTON_PIN, BUTTON_DEBOUNCE_DELAY),
									                  C_Button("est", EST_BUTTON_PIN, BUTTON_DEBOUNCE_DELAY)} ;
C_RotaryEncoder encoder("jog", ENCODER_CLK_PIN, ENCODER_DT_PIN);
C_Selector selectors[NBR_OF_SELECTORS] = {C_Selector("sela", AXIS_SELECTOR_PIN, SELECTOR_DEBOUNCE_DELAY), 
									            	          C_Selector("sels", SCALE_SELECTOR_PIN, SELECTOR_DEBOUNCE_DELAY)};
C_Sender sender;
C_Buffer buffer;

C_EventGenerator* evGenList[NBR_OF_EVENT_GENERATORS];

void setup() {
   Serial.begin(38400);  // opens serial port, sets data rate to 9600 bps
   Serial.setTimeout(500);

   attachInterrupt(digitalPinToInterrupt(ENCODER_CLK_PIN), encoderISR, RISING);

   Serial.println("hej");

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
   String s;
 
   for (i = 0; i<NBR_OF_EVENT_GENERATORS; i++)
   {
      evGenList[i]->scan();
   }

   while(buffer.get(e))
   {
      s  = e.serialize();
      sender.send(s);
   }

   delay(10); // waits 10ms
}

static void encoderISR(void)
{
   encoder.update();
}
