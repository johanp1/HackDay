#include "button.h"
#include "encoder.h"
#include "sender.h"
#include "event_listner.h"
#include "buffer.h"
#include "selector.h"
#include "mpg_pendant.h"

static void encoderISR(void);

C_Button buttons[NBR_OF_BUTTONS] = {C_Button("rth", RTH_BUTTON_PIN, BUTTON_DEBOUNCE_DELAY),
									C_Button("run", RUN_BUTTON_PIN, BUTTON_DEBOUNCE_DELAY),
									C_Button("est", EST_BUTTON_PIN, BUTTON_DEBOUNCE_DELAY)} ;
C_RotaryEncoder encoder("jog", ENCODER_CLK_PIN, ENCODER_DT_PIN);
C_Selector selectors[NBR_OF_SELECTORS] = {C_Selector("sela", AXIS_SELECTOR_PIN, SELECTOR_DEBOUNCE_DELAY), 
										  C_Selector("sels", SCALE_SELECTOR_PIN, SELECTOR_DEBOUNCE_DELAY)};
C_Sender sender;
C_Buffer buffer;

void setup() {
   Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps
   Serial.setTimeout(500);

   attachInterrupt(digitalPinToInterrupt(ENCODER_CLK_PIN), encoderISR, RISING);

   Serial.println("hej");

   buttons[0].addEventListner(&sender);
   buttons[1].addEventListner(&sender);
   buttons[2].addEventListner(&sender);
   selectors[0].addEventListner(&sender);
   selectors[1].addEventListner(&sender);
   encoder.addEventListner(&buffer);
}

void loop() {  

   byte i;
   C_Event e;

   for (i = 0; i<NBR_OF_BUTTONS; i++)
   {
      buttons[i].scan();
   }
  
   for (i = 0; i<NBR_OF_SELECTORS; i++)
   {
      selectors[i].scan();
   }
  
   while(buffer.get(e))
   {
      sender.sendEvent(e);
   }

   delay(10); // waits 10ms
}

static void encoderISR(void)
{
   encoder.update();
}

