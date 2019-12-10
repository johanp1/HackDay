#define debug_print(x)   Serial.print(#x); Serial.print(": "); Serial.println(x);

#include "down_sampler.h"
#include "pulse_stretcher.h"

//the STEPS_PER_STATE needs to be an integer
#define DOWN_SAMPLING_RATIO 5  // we have 500 steps/rev, down sampled with 5 gives output of 100 steps/rev
#define STRETCH_TIME_US 800    // 800 microseconds stretch

// defines pins
const int phaseAInPin = 2;
const int phaseAOutPin = 3;

const int phaseBInPin = 4;
const int phaseBOutPin = 5;

const int indexInPin = 6;
const int indexOutPin = 7;

DownSampler downSamplerA(DOWN_SAMPLING_RATIO);
DownSampler downSamplerB(DOWN_SAMPLING_RATIO);
PulseStretcher pulseStretcher(STRETCH_TIME_US);

void setup() {
  pinMode(phaseAInPin, INPUT);
  pinMode(phaseAOutPin, OUTPUT);

  pinMode(phaseBInPin, INPUT);
  pinMode(phaseBOutPin, OUTPUT);
    
  pinMode(indexInPin, INPUT);
  pinMode(indexOutPin, OUTPUT);
  
  digitalWrite(phaseAOutPin, LOW);
  digitalWrite(phaseBOutPin, LOW);
  digitalWrite(indexOutPin, LOW);
}

void loop() {
  int rawPhaseA = digitalRead(phaseAInPin);
  int rawPhaseB = digitalRead(phaseBInPin);
  int downSampledPhaseA = downSamplerA.update(rawPhaseA);
  int downSampledPhaseB = downSamplerB.update(rawPhaseB);

  int rawIndex = digitalRead(indexInPin);
  int stretchedIndex = pulseStretcher.update(rawIndex);

  digitalWrite(phaseAOutPin, downSampledPhaseA);
  digitalWrite(phaseBOutPin, downSampledPhaseB);
  digitalWrite(indexOutPin, stretchedIndex);
}
