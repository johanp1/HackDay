#include "buffer.h"
#include "button.h"
#include "encoder.h"
#include "sender.h"
#include "event_listner.h"

C_Buffer buffer;
C_Button buttons[2] = { C_Button(&buffer, "x", 3, 50), C_Button(&buffer, "y", 4, 50)} ;
C_RotaryEncoder encoder(2, 4);
C_Sender sender;

void setup() {
  Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(500);

  attachInterrupt(digitalPinToInterrupt(2), encoderISR, CHANGE);

  Serial.println("hej");

  buffer.addEventListner(&sender);
}

void loop() {  
  byte i;

  for (i = 0; i<2; i++)
  {
    buttons[i].scan();
  }
  
/*  while(!buffer.isEmpty())
  {
    handleEvent(buffer.pop());
  }
*/
  delay(10); // waits 10ms
}

void encoderISR(void)
{
  encoder.update();
}

void handleEvent(C_Event *e)
{
  if(e != 0)
  {
    e->who();
  }
  else
  {
    Serial.println("ASSERT!");
  }
}

