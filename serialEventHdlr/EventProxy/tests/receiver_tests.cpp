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
      events.push_back(e);
   };

   void reset()
   {
      events.clear();
   };

   void checkEvent(vector<C_Event>& expectedEvents)
   {
      ASSERT_TRUE(expectedEvents.size() == events.size());

      if (!expectedEvents.empty())
      {
         for (int i = 0; i < expectedEvents.size(); i++)
         {
            String expected_name = expectedEvents.at(i).GetName();
            String expected_data = expectedEvents.at(i).GetData();
            ASSERT_TRUE( events.at(i).GetName().compare(expected_name.s) == 0);
            ASSERT_TRUE( events.at(i).GetData().compare(expected_data.s) == 0);
         }
      }
   }

   void checkEvent(const String& expectedEventName, const String& expectedEventData)
   {
      ASSERT_TRUE(events.size() == 1);
      ASSERT_TRUE(events.at(0).GetName().compare(expectedEventName) == 0);
      ASSERT_TRUE(events.at(0).GetData().compare(expectedEventData) == 0);
   }

   void checkNoEvent()
   {
      ASSERT_TRUE(events.empty());
   }
   
   vector<C_Event> events;
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

TEST_F(ReceiverTestFixture, badMsgRec)
{
   String sendStr = "sa_\n"; //no new-line, event nerver generated

   Serial.setRecData(sendStr);
   r.scan();
   evSpy.checkNoEvent();
}

TEST_F(ReceiverTestFixture, badMsgRec2)
{
   String sendStr = "_"; //no new-line, event nerver generated

   Serial.setRecData(sendStr);
   r.scan();
   evSpy.checkNoEvent();
}

TEST_F(ReceiverTestFixture, badMsgRec3)
{
   String sendStr = "_abc"; //no new-line, event nerver generated

   Serial.setRecData(sendStr);
   r.scan();
   evSpy.checkNoEvent();
}

TEST_F(ReceiverTestFixture, eventOneMsgRec)
{
   String sendStr = "sa\n";
   Serial.setRecData(sendStr);
   r.scan();
   evSpy.checkEvent(String{"sa"}, String{""});
}

TEST_F(ReceiverTestFixture, eventOneMsgRec2)
{
   String sendStr = "sa_123\n";
   Serial.setRecData(sendStr);
   r.scan();
   evSpy.checkEvent(String{"sa"}, String{"123"});
}

TEST_F(ReceiverTestFixture, eventTwoMsgRec)
{
   String sendStr = "apa\nbepa_45\n";
   vector<C_Event> expectedEvents;
   expectedEvents.push_back(C_Event{String("apa"), String("")});
   expectedEvents.push_back(C_Event{String("bepa"), String("45")});

   Serial.setRecData(sendStr);
   r.scan();

   evSpy.checkEvent(expectedEvents);
}

} // namespace