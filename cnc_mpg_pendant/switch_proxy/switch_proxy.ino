#include <button.h>
#include <sender.h>
#include "switch_proxy.h"

C_Button buttons[NBR_OF_SWITCHES] = {C_Button("head", HEAD_ALARM_PIN, BUTTON_DEBOUNCE_DELAY),
									                   C_Button("pos1", TOOL_POS1_PIN, BUTTON_DEBOUNCE_DELAY),
                                     C_Button("posn", TOOL_IN_POS_PIN, BUTTON_DEBOUNCE_DELAY),
									                   C_Button("lube", LUBE_PRESS_OK_PIN, BUTTON_DEBOUNCE_DELAY),
                                     C_Button("estop", ESTOP_BUTTON_PIN, BUTTON_DEBOUNCE_DELAY)};
C_Sender sender;
unsigned long lastScanTime;

void setup() {
   Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps
   Serial.setTimeout(500);

   Serial.println("hej");

   buttons[0].addEventListner(&sender);
   buttons[1].addEventListner(&sender);
   buttons[2].addEventListner(&sender);
   buttons[3].addEventListner(&sender);
   buttons[4].addEventListner(&sender);

   lastScanTime = 0;
}

void loop() {  

   byte i;
   C_Event e;
   unsigned long currTime = millis();

   if(currTime - lastScanTime > BUTTON_DEBOUNCE_DELAY)
   {
      for (i = 0; i<NBR_OF_SWITCHES; i++)
      {
        buttons[i].scan();
      }

      lastScanTime = currTime;
   }
}
