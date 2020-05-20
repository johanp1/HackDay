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
         serializedData = e.serializeData();
         newData++;

         //cout << "serializedData.s " << serializedData.s << endl;
         //cout << "newData " << newData << endl;
      };

      void reset()
      {
         serializedData = String("");
         newData = 0;
      };
      
      String serializedData;
      int newData;
   };

   Receiver r = Receiver("test");
   EventListnerSpy evSpy;
  
   void checkEvent(const String& expected)
   {
      CHECK(evSpy.newData > 0);
      CHECK(evSpy.serializedData.compare(expected) == 0);
   }

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

TEST(ReceiverTestGroup, ScanEmptyRecBuf)
{
   r.scan();
   CHECK(evSpy.newData == 0);
}

TEST(ReceiverTestGroup, ScanOneMsgRec)
{
   String sendStr = "sp_180\n";
   const String& expectedStr = String("sp_180");
   Serial.setRecData(sendStr);
   r.scan();
   CHECK(evSpy.newData > 0);
   checkEvent(expectedStr);
}

TEST(ReceiverTestGroup, eventhalfMsgRec)
{
   String sendStr = "sa_"; //no new-line, event nerver generated

   Serial.setRecData(sendStr);
   r.serialEvent();
   CHECK(evSpy.newData == 0);
}

TEST(ReceiverTestGroup, eventOneMsgRec)
{
   String sendStr = "sa\n";
   String expectedStr = "sa";
   Serial.setRecData(sendStr);
   r.serialEvent();
   CHECK(evSpy.newData > 0);
   checkEvent(expectedStr);
}

TEST(ReceiverTestGroup, eventTwoMsgRec)
{
   String sendStr = "apa\nbepa\n";
   String expectedStr1 = "apa";
   const String& expectedStr2 = "bepa";
   Serial.setRecData(sendStr);
   r.serialEvent();
   CHECK(evSpy.newData > 0);
   
   //checkEvent(expectedStr1);
   //cout << "serializedData " << evSpy.serializedData.s << endl;
   checkEvent(expectedStr2);
}

TEST(ReceiverTestGroup, vectorTest)
{
/*   vector<String> v;
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
   */
}