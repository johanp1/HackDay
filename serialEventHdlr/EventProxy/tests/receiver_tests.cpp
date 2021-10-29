#include <gtest/gtest.h>
#include "receiver.h"
#include "Arduino.h"
#include <iostream>
#include <vector>
using namespace std;

namespace {
class EventListnerSpy : public EventListner{
public:
   void enventListnerSpy()
   {
      reset();
   };
    
   void HandleEvent(C_Event& e)
   {
      serializedData.push_back(e.serializeData());
   };

   void reset()
   {
      serializedData.clear();
   };
      
   void checkEvent(vector<String>& expectedEvents)
   {
      ASSERT_TRUE(expectedEvents.size() == serializedData.size());

      if (!expectedEvents.empty())
      {
         vector<String>::const_iterator expectedDataIterator;
         vector<String>::const_iterator dataIterator;

         for (expectedDataIterator = expectedEvents.begin(), dataIterator = serializedData.begin();
              expectedDataIterator != expectedEvents.end();
              ++expectedDataIterator, ++dataIterator)
         {
            ASSERT_TRUE( (*dataIterator).s.compare( (*expectedDataIterator).s ) == 0);
         }
      }
   }

   void checkEvent(const String& expectedEvent)
   {
      ASSERT_TRUE(serializedData.size() == 1);
      ASSERT_TRUE(serializedData.at(0).compare(expectedEvent) == 0);
   }

   void checkNoEvent()
   {
      ASSERT_TRUE(serializedData.empty());
   }
   
   vector<String> serializedData;
};

class ReceiverTestFixture : public testing::Test 
{
   protected: 
   Receiver r = Receiver("test");
   EventListnerSpy evSpy;
   std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();

   void SetUp()
   {
      arduinoStub->Reset();
      evSpy.reset();
      r.addEventListner(&evSpy);
   }
   
   void TearDown()
   {
      Serial.clear();
   }
};

TEST_F(ReceiverTestFixture, emptyRecBuf)
{
   r.scan();
   evSpy.checkNoEvent();
}

TEST_F(ReceiverTestFixture, halfMsgRec)
{
   String sendStr = "sa_"; //no new-line, event nerver generated

   Serial.setRecData(sendStr);
   r.scan();
   evSpy.checkNoEvent();
}

TEST_F(ReceiverTestFixture, eventOneMsgRec)
{
   String sendStr = "sa\n";
   String expectedStr = "sa";
   Serial.setRecData(sendStr);
   r.scan();
   evSpy.checkEvent(expectedStr);
}
TEST_F(ReceiverTestFixture, eventTwoMsgRec)
{
   String sendStr = "apa\nbepa\n";
   String expectedStr1 = "apa";
   const String& expectedStr2 = "bepa";
   vector<String> expectedEvents;
   expectedEvents.push_back(expectedStr1);
   expectedEvents.push_back(expectedStr2);

   Serial.setRecData(sendStr);
   r.scan();
   evSpy.checkEvent(expectedEvents);
}

/*
TEST_F(ReceiverTestFixture, vectorTest)
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

} // namespace