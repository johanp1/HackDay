#include "button.h"
#include "sender.h"
#include "event_listner.h"
#include "switch_proxy.h"

C_Button buttons[NBR_OF_BUTTONS] = {C_Button("xmin", XMIN_SWITCH_PIN, BUTTON_DEBOUNCE_DELAY),
									C_Button("xmax", XMAX_SWITCH_PIN, BUTTON_DEBOUNCE_DELAY),
                           C_Button("ymin", YMIN_SWITCH_PIN, BUTTON_DEBOUNCE_DELAY),
									C_Button("ymax", YMAX_SWITCH_PIN, BUTTON_DEBOUNCE_DELAY),
                           C_Button("zmin", ZMIN_SWITCH_PIN, BUTTON_DEBOUNCE_DELAY),
									C_Button("zmax", ZMAX_SWITCH_PIN, BUTTON_DEBOUNCE_DELAY),
                           C_Button("est", ESTOP_BUTTON_PIN, BUTTON_DEBOUNCE_DELAY),
									} ;

void setup() {
   Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps
   Serial.setTimeout(500);

   Serial.println("hej");

   buttons[0].addEventListner(&sender);
   buttons[1].addEventListner(&sender);
   buttons[2].addEventListner(&sender);
   buttons[3].addEventListner(&sender);
   buttons[4].addEventListner(&sender);
   buttons[5].addEventListner(&sender);
   buttons[6].addEventListner(&sender);
}

void loop() {  

   byte i;
   C_Event e;

   for (i = 0; i<NBR_OF_BUTTONS; i++)
   {
      buttons[i].scan();
   }

   delay(BUTTON_DEBOUNCE_DELAY);
}
