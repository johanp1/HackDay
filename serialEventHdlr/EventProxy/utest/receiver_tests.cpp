#include "TestHarness.h"
#include "receiver.h"
#include "Arduino.h"
#include <iostream>
#include <vector>
using namespace std;

TEST_GROUP(ReceiverTestGroup)
{
   class EventListnerSpy : public EventListner{
   public:
      void enventListnerSpy()
      {
         reset();
      };
    
      void handleEvent(C_Event& e)
      {
         serializedData.push_back(e.serializeData());
      };

      void reset()
      {
         serializedData.clear();
      };
      
      void checkEvent(vector<String>& expectedEvents)
      {
         CHECK(expectedEvents.size() == serializedData.size());

         if (!expectedEvents.empty())
         {
            vector<String>::const_iterator expectedDataIterator;
            vector<String>::const_iterator dataIterator;

            for (expectedDataIterator = expectedEvents.begin(), dataIterator = serializedData.begin();
                 expectedDataIterator != expectedEvents.end();
                 ++expectedDataIterator, ++dataIterator)
            {
               CHECK( (*dataIterator).s.compare( (*expectedDataIterator).s ) == 0);
            }
         }
      }

      void checkEvent(const String& expectedEvent)
      {
         CHECK(serializedData.size() ==1);
         CHECK(serializedData.at(0).compare(expectedEvent) == 0);
      }

      void checkNoEvent()
      {
         CHECK(serializedData.empty());
      }

      vector<String> serializedData;
   };

   Receiver r = Receiver("test");
   EventListnerSpy evSpy;

   void setup()
   {
      ArduinoStub.reset();
      evSpy.reset();
      r.addEventListner(&evSpy);
   }
   
   void teardown()
   {
      Serial.clear();
   }
};

TEST(ReceiverTestGroup, emptyRecBuf)
{
   r.serialEvent();
   evSpy.checkNoEvent();
}

TEST(ReceiverTestGroup, halfMsgRec)
{
   String sendStr = "sa_"; //no new-line, event nerver generated

   Serial.setRecData(sendStr);
   r.serialEvent();
   evSpy.checkNoEvent();
}

TEST(ReceiverTestGroup, eventOneMsgRec)
{
   String sendStr = "sa\n";
   String expectedStr = "sa";
   Serial.setRecData(sendStr);
   r.serialEvent();
   evSpy.checkEvent(expectedStr);
}

TEST(ReceiverTestGroup, eventTwoMsgRec)
{
   String sendStr = "apa\nbepa\n";
   String expectedStr1 = "apa";
   const String& expectedStr2 = "bepa";
   vector<String> expectedEvents;
   expectedEvents.push_back(expectedStr1);
   expectedEvents.push_back(expectedStr2);

   Serial.setRecData(sendStr);
   r.serialEvent();
   evSpy.checkEvent(expectedEvents);
}

/*
TEST(ReceiverTestGroup, vectorTest)
{
   vector<String> v;
   vector<String>::const_iterator iter;

   v.push_back("0");
   v.push_back("*1");
   v.push_back("**2");
   v.push_back("***3");
   v.push_back("****4");

   for(iter = v.begin(); iter != v.end(); ++iter)
   {
      cout << (*iter).s << endl;
   }
}*/