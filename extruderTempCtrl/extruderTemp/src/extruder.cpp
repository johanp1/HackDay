#include "extruder.h"

#define debug_print(x)   if(debug){Serial.print(#x); Serial.print(": "); Serial.println(x);}

Extruder::Extruder(int tempSensPin_, int pwmPin_) : tempSensPin(tempSensPin_), pwmPin(pwmPin_)
{
   //refTemp = 1000;
  pinMode(pwmPin, OUTPUT);
  pinMode(tempSensPin, INPUT);  // analog read pin
  debug = false;
}

void Extruder::SetDebug(bool d)
{
  debug = d;
  debug_print(debug);
}

void Extruder::SetTempPwmDuty(int d)
{
   analogWrite(pwmPin, d);
}

int Extruder::ReadTemp()
{
  int adc;
  long T;
  long mV;
  
  adc = analogRead(tempSensPin);  // adc 0-1023, 1023 = Vref = 5V
  mV = ((long)adc*5000)/1024;       // converted to milli volt
  debug_print(adc);
  debug_print((int)mV);

  T = (long)(2792500 - ((long)(389*mV)))/1000;  //[0.1 degrees]
  debug_print((int)T);

  return (int)T;
}
