#include "button.h"
#include "encoder.h"
#include "sender.h"
#include "event_listner.h"
#include "buffer.h"

C_Button buttons[2] = { C_Button("x", 3, 50), C_Button("y", 5, 50)} ;
C_RotaryEncoder encoder("rot", 2, 7);
C_Sender sender;
C_Buffer buffer;

void setup() {
  Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(500);

  attachInterrupt(digitalPinToInterrupt(2), encoderISR, CHANGE);

  Serial.println("hej");

  buttons[0].addEventListner(&sender);
  buttons[1].addEventListner(&sender);
  encoder.addEventListner(&buffer);
}

void loop() {  
  byte i;

  for (i = 0; i<2; i++)
  {
    buttons[i].scan();
  }

  if(!buffer.isEmpty())
  {
    C_Event* e = buffer.pop();
    
    sender.sendEvent(*e);
  }
  
  delay(10); // waits 10ms
}

void encoderISR(void)
{
  encoder.update();
}


