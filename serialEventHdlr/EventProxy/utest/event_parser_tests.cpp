#include "TestHarness.h"
#include "event_parser.h"
#include "Arduino.h"
#include <iostream>
TEST_GROUP(EventParserTestGroup)
{
   class ParserFunctionoidSpy : public ParserFunctionoid
   {
      public:
      void executeCmd(void) {hasBeenCalled = true;};
      void clear() {hasBeenCalled = false;};
      bool hasBeenCalled;
   };

   EventParser ep;
   ParserFunctionoidSpy pfs;

   void setup()
   {
   }
  
   void teardown()
   {
   }
};

TEST(EventParserTestGroup, handleValidEvent)
{
   String eventCmdType = String("apa");
   String eventData = String("apa_123");
   String name = String("name");
   C_Event e = C_Event(name, eventData);
   
   ep.addAcceptedCmd(eventCmdType, pfs);
   ep.handleEvent(e);
   cout << "ep.cmdType" << ep.cmdType.s<<endl;
   CHECK(ep.cmdType.compare("apa") == 0 );
   CHECK(ep.cmdVal == 123 );
}
/*
TEST(EventParserTestGroup, handleValidEvent2)
{
   String eventData = String("bepa_456");
   String name = String("name");
   C_Event e = C_Event(name, eventData);
   
   ep.handleEvent(e);
   CHECK(ep.cmdType.compare("bepa") == 0 );
   CHECK(ep.cmdVal == 456 );
}
*/