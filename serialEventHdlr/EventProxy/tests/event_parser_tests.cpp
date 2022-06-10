#include <gtest/gtest.h>
#include "event_parser.h"
#include "Arduino.h"
#include <iostream>

namespace {

class TestCommandHandler : public CommandHandler
{
   public:
   TestCommandHandler(String const& cmd_) : CommandHandler(cmd_), hasBeenCalled{false} {}; 

   void operator()(String& _parsedData)
   {
      hasBeenCalled = true;
      parsedData.s = _parsedData.s;
   };
   
   void operator()(void)
   {
      hasBeenCalled = true;
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
   TestCommandHandler cmdHdlr{String("apa")};

   ParserTestFixture()
   {
      ep.AddAcceptedCmd(cmdHdlr);
   }

   void SetUp()
   {
   }
  
   void TearDown()
   {
      cmdHdlr.clear();
   }
};

TEST_F(ParserTestFixture, init)
{
   ASSERT_TRUE(ep.GetNbrOfAcceptedCmds() == 1);
}

TEST_F(ParserTestFixture, handleValidEvent)
{
   C_Event e{String("apa"),  String("123")};
   
   ASSERT_FALSE(cmdHdlr.hasBeenCalled);

   ep.HandleEvent(e);
   cout << "hej " << cmdHdlr.parsedData.s << '\n';
   ASSERT_TRUE(cmdHdlr.parsedData.compare("123") == 0 );
   ASSERT_TRUE(cmdHdlr.hasBeenCalled);
}

TEST_F(ParserTestFixture, handleUnvalidEvent)
{
   C_Event e{String("hej"), String("321")};
   
   ASSERT_FALSE(cmdHdlr.hasBeenCalled);

   ep.HandleEvent(e);

   ASSERT_FALSE(cmdHdlr.hasBeenCalled);
}

TEST_F(ParserTestFixture, handleUnvalidEvent2)
{
   C_Event e{String("apa_"), String("")};
   
   ASSERT_FALSE(cmdHdlr.hasBeenCalled);

   ep.HandleEvent(e);

   ASSERT_FALSE(cmdHdlr.hasBeenCalled);
}

TEST_F(ParserTestFixture, handleValidEventNoData)
{
   C_Event e{String("apa"), String("")};
   
   ASSERT_FALSE(cmdHdlr.hasBeenCalled);

   ep.HandleEvent(e);
   
   ASSERT_TRUE(cmdHdlr.hasBeenCalled);
}

TEST_F(ParserTestFixture, handle2ValidEvents)
{
   TestCommandHandler cmdHdlr2{String("bepa")};

   C_Event e1{String("apa"), String("5")};
   C_Event e2{String("bepa"), String("xyz")};

    ASSERT_FALSE(cmdHdlr.hasBeenCalled);
    ASSERT_FALSE(cmdHdlr2.hasBeenCalled);
   
   ep.AddAcceptedCmd(cmdHdlr2);
   ASSERT_TRUE(ep.GetNbrOfAcceptedCmds() == 2);

   ep.HandleEvent(e1);

   ASSERT_TRUE(cmdHdlr.parsedData.compare("5") == 0 );
   ASSERT_TRUE(cmdHdlr.hasBeenCalled);
   ASSERT_FALSE(cmdHdlr2.hasBeenCalled);
   cmdHdlr.clear();

   ep.HandleEvent(e2);
   ASSERT_TRUE(cmdHdlr2.parsedData.compare("xyz") == 0 );
   ASSERT_FALSE(cmdHdlr.hasBeenCalled);
   ASSERT_TRUE(cmdHdlr2.hasBeenCalled);
}

} // namespace