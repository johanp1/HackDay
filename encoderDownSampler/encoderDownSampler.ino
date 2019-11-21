#define debug_print(x)   Serial.print(#x); Serial.print(": "); Serial.println(x);

#include "down_sampler.h"
#include "pulse_stretcher.h"

//the STEPS_PER_STATE needs to be an integer
#define DOWN_SAMPLING_RATIO 5  // we have 500 steps/rev, down sampled with 5 gives output of 100 steps/rev
#define STRETCH_TIME_US 800    // 800 microseconds stretch

// defines pins
const int phaseInPin = 3;
const int phaseOutPin = 4;

const int indexInPin = 4;
const int indexOutPin = 5;

DownSampler downSampler(DOWN_SAMPLING_RATIO);
PulseStretcher pulseStretcher(STRETCH_TIME_US);

void setup() {
  pinMode(phaseInPin, INPUT);
  pinMode(phaseOutPin, OUTPUT);
  
  digitalWrite(phaseOutPin, LOW);
}

void loop() {
  int rawPhase = digitalRead(phaseInPin);
  int downSampledPhase = downSampler.update(rawPhase);

  int rawIndex = digitalRead(indexInPin);
  int stretchedIndex = pulseStretcher.update(rawIndex);

  digitalWrite(phaseOutPin, downSampledPhase);
  digitalWrite(indexOutPin, stretchedIndex);
}
