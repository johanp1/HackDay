#include "TestHarness.h"
#include "down_sampler.h"

TEST_GROUP(DownSamplerTestGroup)
{  
  void setup()
  {  
  }
  
  void teardown()
  {
  }

};

TEST(DownSamplerTestGroup, testUpdateNoPulse)
{
  int currState;
  DownSampler downSampler(2);
  
  currState = downSampler.update(0);
  CHECK(currState == 0);
}

TEST(DownSamplerTestGroup, testUpdateNoPulse)
{
  int currState;
  DownSampler downSampler(2);

  currState = downSampler.update(1);
  CHECK(currState == 1);
  
  currState = downSampler.update(1);
  CHECK(currState == 1);
  
  currState = downSampler.update(1);
  CHECK(currState == 1);
  
  currState = downSampler.update(0);
  CHECK(currState == 1);
  
  currState = downSampler.update(0);
  CHECK(currState == 1);
  
  currState = downSampler.update(0);
  CHECK(currState == 1);
  
  currState = downSampler.update(1);
  CHECK(currState == 0);
}

TEST(DownSamplerTestGroup, testDownSampleRatio2)
{
  int currState;
  DownSampler downSampler(2);

  currState = downSampler.update(1);
  CHECK(currState == 1);

  currState = downSampler.update(0);
  CHECK(currState == 1);

  currState = downSampler.update(1);
  CHECK(currState == 0);

  currState = downSampler.update(0);
  CHECK(currState == 0);

  currState = downSampler.update(1);
  CHECK(currState == 1);
  
}

TEST(DownSamplerTestGroup, testDownSampleRatio5)
{
  int currState;
  DownSampler downSampler(5);

  currState = downSampler.update(1);
  CHECK(currState == 1);

  currState = downSampler.update(0);
  CHECK(currState == 1);

  currState = downSampler.update(1);
  CHECK(currState == 1);

  currState = downSampler.update(0);
  CHECK(currState == 1);

  currState = downSampler.update(1);
  CHECK(currState == 0);

  currState = downSampler.update(0);
  CHECK(currState == 0);

  currState = downSampler.update(1);
  CHECK(currState == 0);

  currState = downSampler.update(0);
  CHECK(currState == 0);

  currState = downSampler.update(1);
  CHECK(currState == 0);

  currState = downSampler.update(0);
  CHECK(currState == 0);

  currState = downSampler.update(1);
  CHECK(currState == 1);
  
}

