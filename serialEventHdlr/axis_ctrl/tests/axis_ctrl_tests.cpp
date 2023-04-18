#include "gtest/gtest.h"
//#include "gmock/gmock.h"
#include "axis_ctrl.h"
#include <memory>
#include <iostream>
#include <sstream>

namespace {

class AxisCtrlTestFixture : public testing::Test 
{
  protected:
   void SetUp()
   {
   }
   
   void TearDown()
   {
   }
   
   void incTime(milli_sec t = 1)
   {
   
   }
};

TEST(AxisCtrlTestGroup, test_init)
{
   AxisCtrl ac();
   ASSERT_TRUE(true);   
}

}