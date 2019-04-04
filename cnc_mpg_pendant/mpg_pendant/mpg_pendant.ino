#include "buffer.h"
#include "button.h"
#include "encoder.h"

C_Buffer buffer;
C_Button button(&buffer, "x", 3, 50);
C_RotaryEncoder encoder(2, 4);

void setup() {
  Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(500);

  attachInterrupt(digitalPinToInterrupt(2), encoderISR, CHANGE);

  Serial.println("hej");
}

void loop() {
  byte data;
  
  while(buffer.pop(&data))
  {
    Serial.println(data);
  }

  button.scan();

  delay(10); // waits 10ms
}

void encoderISR(void)
{
  encoder.update();
}


