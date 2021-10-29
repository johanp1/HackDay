#include <gtest/gtest.h>
#include "event_parser.h"
#include "Arduino.h"
#include <iostream>

namespace {
class ParserFunctionoidSpy : public ParserFunctionoid
{
   public:
   ParserFunctionoidSpy(String const& cmd_) : ParserFunctionoid(cmd_){}; 

   void execute(String& _parsedData)
   {
      hasBeenCalled = true;
      parsedData.s = _parsedData.s;
      //std::cout << _parsedData.s << std::endl;
   };
      
   void clear()
   {
      hasBeenCalled = false;
      parsedData.s.clear();
   };

   bool hasBeenCalled;
   String parsedData;
};

class ParserTestFixture : public testing::Test 
{
   protected: 
   EventParser ep;
   ParserFunctionoidSpy pfSpy{String("apa")};

   void SetUp()
   {
      String eventCmd = String("apa");
      ep.AddAcceptedCmd(pfSpy);
   }
  
   void TearDown()
   {
      pfSpy.clear();
   }
};

TEST_F(ParserTestFixture, init)
{
   ASSERT_TRUE(ep.GetNbrOfAcceptedCmds() == 1);
}

TEST_F(ParserTestFixture, handleValidEvent)
{
   C_Event e{String("dummy"),  String("apa_123")};
   
   ASSERT_TRUE(!pfSpy.hasBeenCalled);

   ep.HandleEvent(e);
   
   ASSERT_TRUE(pfSpy.parsedData.compare("123") == 0 );
   ASSERT_TRUE(pfSpy.hasBeenCalled);
}

TEST_F(ParserTestFixture, handleUnvalidEvent)
{
   C_Event e{String("dummy"), String("hej_321")};
   
   ASSERT_TRUE(!pfSpy.hasBeenCalled);

   ep.HandleEvent(e);

   ASSERT_TRUE(!pfSpy.hasBeenCalled);
}

TEST_F(ParserTestFixture, handleUnvalidEvent2)
{
   C_Event e{String("dummy"), String("apa_")};
   
   ASSERT_TRUE(!pfSpy.hasBeenCalled);

   ep.HandleEvent(e);

   ASSERT_TRUE(!pfSpy.hasBeenCalled);
}

TEST_F(ParserTestFixture, handleUnvalidEvent3)
{
   C_Event e{String("dummy"), String("apa123")};
   
   ASSERT_TRUE(!pfSpy.hasBeenCalled);

   ep.HandleEvent(e);

   ASSERT_TRUE(!pfSpy.hasBeenCalled);
}

TEST_F(ParserTestFixture, handleValidEventNoData)
{
   C_Event e{String("dummy"), String("apa")};
   
   ASSERT_TRUE(!pfSpy.hasBeenCalled);

   ep.HandleEvent(e);
   
   ASSERT_TRUE(pfSpy.parsedData.compare("") == 0 );
   ASSERT_TRUE(pfSpy.hasBeenCalled);
}

TEST_F(ParserTestFixture, handle2ValidEvent)
{
   ParserFunctionoidSpy pfSpy2{"bepa"};

   C_Event e1{String("dummy"), String("apa_5")};
   C_Event e2{String("dummy"), String("bepa_xyz")};

   ASSERT_TRUE(!pfSpy.hasBeenCalled);
   ASSERT_TRUE(!pfSpy2.hasBeenCalled);
   
   ep.AddAcceptedCmd(pfSpy2);

   ep.HandleEvent(e1);

   ASSERT_TRUE(pfSpy.parsedData.compare("5") == 0 );
   ASSERT_TRUE(pfSpy.hasBeenCalled);
   ASSERT_TRUE(!pfSpy2.hasBeenCalled);
   pfSpy.clear();

   ep.HandleEvent(e2);
   ASSERT_TRUE(pfSpy2.parsedData.compare("xyz") == 0 );
   ASSERT_TRUE(!pfSpy.hasBeenCalled);
   ASSERT_TRUE(pfSpy2.hasBeenCalled);
}
} // namespace