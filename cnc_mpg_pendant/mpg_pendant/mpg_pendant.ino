#include "buffer.h"
#include "button.h"
#include "encoder.h"

C_Buffer buffer;
C_Button button(3, 100);
C_RotaryEncoder encoder(2, 4);

void setup() {
  buffer.push('h'); 
  buffer.push('e');
  buffer.push('j');

  Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(500);

  attachInterrupt(digitalPinToInterrupt(2), encoderISR, CHANGE);
}

void loop() {
  byte data;
  
  while(buffer.pop(&data))
  {
    Serial.print((char)data);
  }

  if(button.scan() == HIGH)
  {
    //buffer.push('1');
    Serial.print('*');
  }

  Serial.print("encoder: ");
  Serial.println(encoder.getPosition());

  delay(50); // waits 100ms
}

void encoderISR(void)
{
  encoder.update();
}


