#define debug_print(x)   Serial.print(#x); Serial.print(": "); Serial.println(x);

#include "down_sampler.h"

//the STEPS_PER_STATE needs to be an integer
#define DOWN_SAMPLING_RATIO 5  // we have 500 steps/rev, down sampled with 5 gives output of 100 steps/rev

// defines pins
const int encoderInPin = 3;
const int outPin = 4;

DownSampler downSampler(DOWN_SAMPLING_RATIO);

void setup() {
  pinMode(encoderInPin, INPUT);
  pinMode(outPin, OUTPUT);
  
  digitalWrite(outPin, LOW);
}

void loop() {
  int currVal = digitalRead(encoderInPin);
  int out = downSampler.update(currVal);
  digitalWrite(outPin, out);
}
