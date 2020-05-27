#include "TestHarness.h"
#include "event_parser.h"
#include "Arduino.h"
#include <iostream>
TEST_GROUP(EventParserTestGroup)
{
   class ParserFunctionoidSpy : public ParserFunctionoid
   {
      public:
      void execute(String& _parsedData)
      {
         hasBeenCalled = true;
         parsedData.s = _parsedData.s;
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
   ParserFunctionoidSpy pfSpy;

   void setup()
   {
      String eventCmd = String("apa");
      ep.addAcceptedCmd(eventCmd, pfSpy);
   }
  
   void teardown()
   {
      pfSpy.clear();
   }
};

TEST(EventParserTestGroup, handleValidEvent)
{
   String eventData = String("apa123");
   String name = String("dummy");
   C_Event e = C_Event(name, eventData);
   
   CHECK(!pfSpy.hasBeenCalled);

   ep.handleEvent(e);
   
   CHECK(pfSpy.parsedData.compare("123") == 0 );
   CHECK(pfSpy.hasBeenCalled);
}

TEST(EventParserTestGroup, handleValidEvent2)
{
   String eventCmdType = String("bepa");
   String eventData = String("bepa456");
   String name = String("dummy");
   C_Event e = C_Event(name, eventData);

   CHECK(!pfSpy.hasBeenCalled);

   ep.addAcceptedCmd(eventCmdType, pfSpy);

   ep.handleEvent(e);

   CHECK(pfSpy.parsedData.compare("456") == 0 );
   CHECK(pfSpy.hasBeenCalled);
}

TEST(EventParserTestGroup, handleUnvalidEvent)
{
   String eventData = String("hej321");
   String name = String("dummy");
   C_Event e = C_Event(name, eventData);
   
   CHECK(!pfSpy.hasBeenCalled);

   ep.handleEvent(e);

   CHECK(!pfSpy.hasBeenCalled);
}

TEST(EventParserTestGroup, handleValidEventNoData)
{
    String eventData = String("apa");
   String name = String("dummy");
   C_Event e = C_Event(name, eventData);
   
   CHECK(!pfSpy.hasBeenCalled);

   ep.handleEvent(e);
   
   CHECK(pfSpy.parsedData.compare("") == 0 );
   CHECK(pfSpy.hasBeenCalled);
}

TEST(EventParserTestGroup, handle2ValidEvent)
{
   ParserFunctionoidSpy myPfSpy;
   String eventData1 = String("apa5");
   String eventCmd2 = String("bepa");
   String eventData2 = String("bepaxyz");
   String name = String("dummy");

   C_Event e1 = C_Event(name, eventData1);
   C_Event e2 = C_Event(name, eventData2);

   CHECK(!pfSpy.hasBeenCalled);
   CHECK(!myPfSpy.hasBeenCalled);
   
   ep.addAcceptedCmd(eventCmd2, myPfSpy);

   ep.handleEvent(e1);

   CHECK(pfSpy.parsedData.compare("5") == 0 );
   CHECK(pfSpy.hasBeenCalled);
   CHECK(!myPfSpy.hasBeenCalled);
   pfSpy.clear();

   ep.handleEvent(e2);
   CHECK(myPfSpy.parsedData.compare("xyz") == 0 );
   CHECK(!pfSpy.hasBeenCalled);
   CHECK(myPfSpy.hasBeenCalled);
}
