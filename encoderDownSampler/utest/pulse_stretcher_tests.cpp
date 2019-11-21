#include "TestHarness.h"
#include "pulse_stretcher.h"

TEST_GROUP(PulseStretcherTestGroup)
{  
  void setup()
  {  
  }
  
  void teardown()
  {
    ArduinoStub.reset();
  }

};

TEST(PulseStretcherTestGroup, testUpdateNoPulse)
{
  int output;
  PulseStretcher pulseStretcher(2);
  
  output = pulseStretcher.update(0);
  CHECK(output == 0);
}

TEST(PulseStretcherTestGroup, testStartStretching)
{
  int output;
  PulseStretcher pulseStretcher(2);
  
  output = pulseStretcher.update(1);
  CHECK(output == 1);

  output = pulseStretcher.update(0);
  CHECK(output == 1);
}

TEST(PulseStretcherTestGroup, testStopStretch)
{
  int output;
  PulseStretcher pulseStretcher(800);
  
  output = pulseStretcher.update(1);
  CHECK(output == 1);

  output = pulseStretcher.update(0);
  CHECK(output == 1);

  ArduinoStub.incTime(799);
  output = pulseStretcher.update(0);
  CHECK(output == 1);

  ArduinoStub.incTime(1);
  output = pulseStretcher.update(0);
  CHECK(output == 0);
}

TEST(PulseStretcherTestGroup, testTimeOverflow)
{
  int output;
  PulseStretcher pulseStretcher(2);
  
  ArduinoStub.incTime(0xffffffffffffffff-1);

  output = pulseStretcher.update(1);
  CHECK(output == 1);

  output = pulseStretcher.update(0);
  CHECK(output == 1);

  ArduinoStub.incTime(1);
  output = pulseStretcher.update(0);
  CHECK(output == 1);

  ArduinoStub.incTime(1);
  output = pulseStretcher.update(0);
  CHECK(output == 0);
}