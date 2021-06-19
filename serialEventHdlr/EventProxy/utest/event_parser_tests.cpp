#include "TestHarness.h"
#include "event_parser.h"
#include "Arduino.h"
#include <iostream>
TEST_GROUP(EventParserTestGroup)
{
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

   EventParser ep;
   ParserFunctionoidSpy pfSpy{String("apa")};

   void setup()
   {
      String eventCmd = String("apa");
      ep.AddAcceptedCmd(pfSpy);
   }
  
   void teardown()
   {
      pfSpy.clear();
   }
};

TEST(EventParserTestGroup, init)
{
   CHECK(ep.GetNbrOfAcceptedCmds() == 1);
}

TEST(EventParserTestGroup, handleValidEvent)
{
   C_Event e{String("dummy"),  String("apa_123")};
   
   CHECK(!pfSpy.hasBeenCalled);

   ep.HandleEvent(e);
   
   CHECK(pfSpy.parsedData.compare("123") == 0 );
   CHECK(pfSpy.hasBeenCalled);
}

TEST(EventParserTestGroup, handleUnvalidEvent)
{
   C_Event e{String("dummy"), String("hej_321")};
   
   CHECK(!pfSpy.hasBeenCalled);

   ep.HandleEvent(e);

   CHECK(!pfSpy.hasBeenCalled);
}

TEST(EventParserTestGroup, handleUnvalidEvent2)
{
   C_Event e{String("dummy"), String("apa_")};
   
   CHECK(!pfSpy.hasBeenCalled);

   ep.HandleEvent(e);

   CHECK(!pfSpy.hasBeenCalled);
}

TEST(EventParserTestGroup, handleUnvalidEvent3)
{
   C_Event e{String("dummy"), String("apa123")};
   
   CHECK(!pfSpy.hasBeenCalled);

   ep.HandleEvent(e);

   CHECK(!pfSpy.hasBeenCalled);
}

TEST(EventParserTestGroup, handleValidEventNoData)
{
   C_Event e{String("dummy"), String("apa")};
   
   CHECK(!pfSpy.hasBeenCalled);

   ep.HandleEvent(e);
   
   CHECK(pfSpy.parsedData.compare("") == 0 );
   CHECK(pfSpy.hasBeenCalled);
}

TEST(EventParserTestGroup, handle2ValidEvent)
{
   ParserFunctionoidSpy pfSpy2{"bepa"};

   C_Event e1{String("dummy"), String("apa_5")};
   C_Event e2{String("dummy"), String("bepa_xyz")};

   CHECK(!pfSpy.hasBeenCalled);
   CHECK(!pfSpy2.hasBeenCalled);
   
   ep.AddAcceptedCmd(pfSpy2);

   ep.HandleEvent(e1);

   CHECK(pfSpy.parsedData.compare("5") == 0 );
   CHECK(pfSpy.hasBeenCalled);
   CHECK(!pfSpy2.hasBeenCalled);
   pfSpy.clear();

   ep.HandleEvent(e2);
   CHECK(pfSpy2.parsedData.compare("xyz") == 0 );
   CHECK(!pfSpy.hasBeenCalled);
   CHECK(pfSpy2.hasBeenCalled);
}
