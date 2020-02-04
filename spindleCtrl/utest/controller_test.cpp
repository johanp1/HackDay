#include "TestHarness.h"
#include "controller.h"
#include <iostream>
using namespace std;

TEST_GROUP(ControllerTestGroup)
{
  Controller* c;

  void setup()
  {
     c = new Controller(100);
  }
  
  void teardown()
  {
     delete c;
  }

};
/*
TEST(ControllerTestGroup, testInit)
{
   int u;
   u = c->run();
    cout << "u: " << u << "\n";
   LONGS_EQUAL(0, u);
}
*/
TEST(ControllerTestGroup, testSetpoint)
{
   int u;
   int i;

   c->setSpeedRef(1);
   
   for (i = 0; i < 2; i++)
   {
      u = c->run();
      cout << "u: " << u << "\n";
   }
   //LONGS_EQUAL(0, u);
}