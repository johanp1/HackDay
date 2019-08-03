#include "button.h"
#include "encoder.h"
#include "sender.h"
#include "event_listner.h"
#include "buffer.h"
#include "selector.h"

#define NBR_OF_BUTTONS 3
#define NBR_OF_SELECTORS 2

C_Button buttons[NBR_OF_BUTTONS] = { C_Button("rth", 3, 50), C_Button("run", 6, 50), C_Button("est", 8, 50)} ;
C_RotaryEncoder encoder("jog", 2, 7);
C_Selector selectors[NBR_OF_SELECTORS] = {C_Selector("sela", A3, 100), C_Selector("sels", A2, 100)};
C_Sender sender;
C_Buffer buffer;

void setup() {
  Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(500);

  attachInterrupt(digitalPinToInterrupt(2), encoderISR, CHANGE);

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

void encoderISR(void)
{
  encoder.update();
}

