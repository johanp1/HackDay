#include <gtest/gtest.h>
#include "event_generator.h"
#include "Arduino.h"

constexpr int PIN = 3;

namespace {
class EventListnerSpy : public EventListner{
public:
   void enventListnerSpy()
   {
      reset();
   };
    
   void HandleEvent(C_Event& e)
   {
      newData = true;
      serializedEvent = e.serialize();
   };

   void reset()
   {
      serializedEvent = "";
      newData = false;
   }
    
   String serializedEvent;
   bool newData;
};

class TestEventGenerator : public EventGenerator{
   public:
   TestEventGenerator(const String& argName) : EventGenerator(argName){};
   void scan(void){};
};

class EventGeneratorTestFixture : public testing::Test 
{  
   protected: 
   std::unique_ptr<TestEventGenerator> generator;
   EventListnerSpy evSpy;

   void SetUp() override
   {
      generator = std::make_unique<TestEventGenerator>("test");
      generator->addEventListner(&evSpy);
   }
   
   void TearDown()
   {
      generator.reset();
   }
};

TEST_F(EventGeneratorTestFixture, Init)
{
  ASSERT_TRUE(true);
}

TEST_F(EventGeneratorTestFixture, generateEventStringArg)
{
   ASSERT_FALSE(evSpy.newData);
   generator->generateEvent(String{"123"});
   ASSERT_TRUE(evSpy.newData);
   ASSERT_TRUE(evSpy.serializedEvent.compare("test_123") == 0);
}

TEST_F(EventGeneratorTestFixture, generateEventCharArrayArg)
{
   ASSERT_FALSE(evSpy.newData);
   generator->generateEvent("bepa");
   ASSERT_TRUE(evSpy.newData);
   ASSERT_TRUE(evSpy.serializedEvent.compare("test_bepa") == 0);
}

TEST_F(EventGeneratorTestFixture, generateEventIntegerArg)
{
   ASSERT_FALSE(evSpy.newData);
   generator->generateEvent(99);
   ASSERT_TRUE(evSpy.newData);
   ASSERT_TRUE(evSpy.serializedEvent.compare("test_99") == 0);
}

TEST_F(EventGeneratorTestFixture, generateEventFloatArg)
{
   ASSERT_FALSE(evSpy.newData);
   generator->generateEvent(99.99f);
   ASSERT_TRUE(evSpy.newData);
   ASSERT_TRUE(evSpy.serializedEvent.compare("test_99.99") == 0);
}

TEST_F(EventGeneratorTestFixture, generateEventNameAndFloatArg)
{
   ASSERT_FALSE(evSpy.newData);
   generator->generateEvent(String{"apa"}, 99.99f);
   ASSERT_TRUE(evSpy.newData);
   ASSERT_TRUE(evSpy.serializedEvent.compare("apa_99.99") == 0);
}

TEST_F(EventGeneratorTestFixture, twoListners)
{
   EventListnerSpy evSpy2;
   generator->addEventListner(&evSpy2);

   ASSERT_FALSE(evSpy.newData);
   ASSERT_FALSE(evSpy2.newData);

   generator->generateEvent(1);
   cout << evSpy.serializedEvent.s << "\n";
   cout << evSpy2.serializedEvent.s << "\n";
   ASSERT_TRUE(evSpy.newData);
   ASSERT_TRUE(evSpy2.newData);
   ASSERT_TRUE(evSpy.serializedEvent.compare("test_1") == 0);
   ASSERT_TRUE(evSpy2.serializedEvent.compare("test_1") == 0);
}

} // namespace
