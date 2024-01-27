#include <gtest/gtest.h>
#include "controller.h"
#include "Arduino.h"
#include <iostream>

namespace {

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
   
   ASSERT_TRUE(p1.K == 2);
   ASSERT_TRUE(p1.Ti == 12000);
   ASSERT_TRUE(p1.Td == 0);
   ASSERT_TRUE(p1.N == 10);
   ASSERT_TRUE(p1.Tr == 3000);
   ASSERT_TRUE(p1.beta == 1);

   ASSERT_TRUE(p2.K == 0);
   ASSERT_TRUE(p2.Ti == 0);
   ASSERT_TRUE(p2.Td == 0);
   ASSERT_TRUE(p2.N == 0);
   ASSERT_TRUE(p2.Tr == 0);
   ASSERT_TRUE(p2.beta == 0);

   ASSERT_TRUE(p3 == p1);
   ASSERT_TRUE(p1 != p2);
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
   ASSERT_TRUE(p == tempCtrl.GetPar());
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
   tempCtrl.SetRef(1);
   tempCtrl.Step(0);
   ASSERT_TRUE(tempCtrl.GetOut() == 0);
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
   tempCtrl.SetEnabled(true);

   tempCtrl.SetRef(1);
   tempCtrl.Step(0);
   ASSERT_TRUE(tempCtrl.GetOut() == 1);

   tempCtrl.SetRef(1);
   tempCtrl.Step(0);
   ASSERT_TRUE(tempCtrl.GetOut() == 5); // check saturated
}

TEST(ControllerTestGroup, setDebug)
{
   PIDController tempCtrl(100);

   tempCtrl.SetDebug(0);
   ASSERT_TRUE(Serial.getData().compare(""s) == 0);

   string expected = string("controller::debug_: 1\n");
   tempCtrl.SetDebug(1);
   ASSERT_TRUE(Serial.getData().compare(expected) == 0);
}
}