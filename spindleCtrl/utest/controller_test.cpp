#include "TestHarness.h"
#include "controller.h"
#include <iostream>
using namespace std;

TEST_GROUP(ControllerTestGroup)
{
  Controller* c;

  void setup()
  {
    cout<<"1;";
     c = new Controller(100);
     cout<<"*1;\n";
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
   
   c->setSpeedRef(10);
   
   for (i = 0; i < 2; i++)
   {
      u = c->run();
   }

   c->setSpeed(10);
   
   for (i = 0; i < 2; i++)
   {
      u = c->run();
   }

   cout << "final u: " << u;
   //LONGS_EQUAL(0, u);
}
