#include "extruder.h"

#define debug_print(x)   if(debug_){Serial.print("extruder::");Serial.print(#x); Serial.print(": "); Serial.println(x);}

Extruder::Extruder(int tempSensPin, int pwmPin) : tempSensPin_(tempSensPin), pwmPin_(pwmPin)
{
  pinMode(pwmPin_, OUTPUT);
  pinMode(tempSensPin_, INPUT);  // analog read pin

  SetDebug(false);
  SetEnabled(false);
}

void Extruder::SetDebug(bool d)
{
  debug_ = d;
  debug_print(debug_);
}

void Extruder::SetEnabled(bool e)
{
  enabled_ = e;
  debug_print(enabled_);

  if (!enabled_)
  {
    analogWrite(pwmPin_, 0);
  }
}

bool Extruder::IsEnabled()
{
   return enabled_;
}

void Extruder::SetTempPwmDuty(int d)
{
  if (enabled_)
  {
    analogWrite(pwmPin_, d);
  }
}

int Extruder::ReadTemp()
{
  int adc;
  long T;
  long mV;
  
  adc = analogRead(tempSensPin_);  // adc 0-1023, 1023 = Vref = 5V
  mV = ((long)adc*5000)/1024;       // converted to milli volt
  debug_print(adc);
  debug_print((int)mV);

  T = (long)(2792500 - ((long)(389*mV)))/1000;  //[0.1 degrees]
  debug_print((int)T);

  return (int)T;
}
