#define debug_print(x)   Serial.print(#x); Serial.print(": "); Serial.println(x);

#include "down_sampler.h"

//the STEPS_PER_STATE needs to be an integer
#define DOWN_SAMPLING_RATIO 4  // we have 500 steps/rev, down sampled with 4 gives output of 125 steps/rev
#define STEPS_PER_STATE DOWN_SAMPLING_RATIO/2

// defines pins
const int encoderInPin = 3;
const int outPin = 4;

int stepCount;
int prevVal;
int outPinState;

void setup() {
  pinMode(encoderInPin, INPUT);
  pinMode(outPin, OUTPUT);

  stepCount = 0;
  prevVal = 0;
  outPinState = LOW;
  
  digitalWrite(outPin, LOW);
}

void loop() {
  int currVal = digitalRead(encoderInPin);

  //count positive flanks
  if ((prevVal == LOW) && (currVal == HIGH))
  {
    stepCount++;
    prevVal = currVal;
  }
  
  if (stepCount >= STEPS_PER_STATE)
  {
    //toggle outPin
    outPinState = outPinState == LOW ? LOW : HIGH;
    
    stepCount = 0;
    digitalWrite(outPin, outPinState);
  }
}
