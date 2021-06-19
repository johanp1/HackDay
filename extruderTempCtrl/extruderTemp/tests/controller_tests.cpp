#include "TestHarness.h"
#include "controller.h"
#include "Arduino.h"
#include <iostream>

TEST_GROUP(ControllerTestGroup)
{
   //Sender s;
  
   void setup()
   {  
   }
  
   void teardown()
   {
   }
};

TEST(ControllerTestGroup, creatingParameters)
{
   PIDParameters p1(2,     // K, 
                    12000, // Ti
                    0,     // Td 
                    10,    // N 
                    3000,  // Tr
                    1);    // beta

   PIDParameters p2;
   PIDParameters p3(p1);
   
   CHECK(p1.K == 2);
   CHECK(p1.Ti == 12000);
   CHECK(p1.Td == 0);
   CHECK(p1.N == 10);
   CHECK(p1.Tr == 3000);
   CHECK(p1.beta == 1);

   CHECK(p2.K == 0);
   CHECK(p2.Ti == 0);
   CHECK(p2.Td == 0);
   CHECK(p2.N == 0);
   CHECK(p2.Tr == 0);
   CHECK(p2.beta == 0);

   CHECK(p3 == p1);
   CHECK(p1 != p2);
}
   //PIDController tempCtrl(1000, p, 0, 200);


TEST(ControllerTestGroup, initController)
{
   PIDParameters p(1, // K, 
                   2, // Ti
                   3, // Td 
                   4, // N 
                   5, // Tr
                   6);// beta

   PIDController tempCtrl(1000, p, 0, 200);
   CHECK(p == tempCtrl.GetPar());
}

TEST(ControllerTestGroup, outputWhenDisabled)
{
   PIDParameters p(1, // K, 
                   1, // Ti
                   1, // Td 
                   1, // N 
                   1, // Tr
                   1);// beta

   PIDController tempCtrl(1000, p, 0, 5);
   
   CHECK(tempCtrl.Step(0, 1) == 0);
}

TEST(ControllerTestGroup, CalcOutput)
{
   PIDParameters p(1, // K, 
                   1, // Ti
                   1, // Td 
                   1, // N 
                   1, // Tr
                   1);// beta

   PIDController tempCtrl(1000, p, 0, 5);
   tempCtrl.SetEnable(true);
   CHECK(tempCtrl.Step(0, 1) == 1);
   CHECK(tempCtrl.Step(0, 1) == 5); // check saturated
}

TEST(ControllerTestGroup, setDebug)
{
   PIDController tempCtrl(100);

   tempCtrl.SetDebug(0);
   CHECK(Serial.getData().compare(""s) == 0);

   string expected = string("debug: 1\n");
   tempCtrl.SetDebug(1);
   CHECK(Serial.getData().compare(expected) == 0);
}