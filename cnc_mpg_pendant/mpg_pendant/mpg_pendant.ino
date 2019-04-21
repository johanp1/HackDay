#include "button.h"
#include "encoder.h"
#include "sender.h"
#include "event_listner.h"
#include "buffer.h"
#include "selector.h"

C_Button buttons[3] = { C_Button("rth", 3, 50), C_Button("run", 5, 50), C_Button("est", 8, 50)} ;
C_RotaryEncoder encoder("jog", 2, 7);
C_Selector selector("sel", A3, 100);
C_Sender sender;
C_Buffer buffer;

void setup() {
  Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(500);

  attachInterrupt(digitalPinToInterrupt(2), encoderISR, CHANGE);

  Serial.println("hej");

  buttons[0].addEventListner(&sender);
  buttons[1].addEventListner(&sender);
  selector.addEventListner(&sender);
  encoder.addEventListner(&buffer);
}

void loop() {  
  byte i;
  C_Event e;

  for (i = 0; i<2; i++)
  {
    buttons[i].scan();
  }

  selector.scan();

  if(buffer.pop(e))
  {
    sender.sendEvent(e);
  }
  
  delay(10); // waits 10ms
}

void encoderISR(void)
{
  encoder.update();
}


