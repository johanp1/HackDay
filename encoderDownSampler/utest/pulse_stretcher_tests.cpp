#include "TestHarness.h"
#include "pulse_stretcher.h"

TEST_GROUP(PulseStretcherTestGroup)
{  
  void setup()
  {  
  }
  
  void teardown()
  {
  }

};

TEST(PulseStretcherTestGroup, testUpdateNoPulse)
{
  int output;
  PulseStretcher pulseStretcher(2);
  
  output = pulseStretcher.update(0);
  CHECK(output == 0);
}

TEST(PulseStretcherTestGroup, testStretchSimple)
{
  int output;
  PulseStretcher pulseStretcher(2);
  
  output = pulseStretcher.update(1);
  CHECK(output == 1);

  output = pulseStretcher.update(0);
  CHECK(output == 1);
}

TEST(PulseStretcherTestGroup, testStretch)
{
  int output;
  PulseStretcher pulseStretcher(2);
  
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