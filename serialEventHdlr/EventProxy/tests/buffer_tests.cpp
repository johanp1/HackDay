#include <gtest/gtest.h>
#include "buffer.h"

namespace {
class BufferTestFixture : public testing::Test 
{
  protected: 
  Buffer buffer;
  
  void SetUp() override
  {  
  }
    
  void TearDown()
  {
    buffer.flush();
  }

  void fillBuffer(int seed, int nbr)
  {
    String s = String("test");
      
    for (int i = 0; i < nbr; i++)
    {
      buffer.put(C_Event(s, (unsigned int)(seed+i)));
    }
  }
};

TEST_F(BufferTestFixture, EmptyAfterCreation)
{
  ASSERT_TRUE(buffer.isEmpty());
}

TEST_F(BufferTestFixture, NotEmpty)
{
  buffer.put(C_Event());
  ASSERT_TRUE(!buffer.isEmpty());
}

TEST_F(BufferTestFixture, GetEmpty)
{
  C_Event e;
  ASSERT_TRUE(!buffer.get(e));
}


TEST_F(BufferTestFixture, NotEmptyThenEmpty)
{
  C_Event e;
  
  buffer.put(C_Event());
  ASSERT_TRUE(!buffer.isEmpty());
  ASSERT_TRUE(buffer.get(e));
  ASSERT_TRUE(buffer.isEmpty());
}


TEST_F(BufferTestFixture, GetPutOneValue)
{
  C_Event e;
  String str = String("hej");
  String expected;
  
  buffer.put(C_Event(str, 1));
  ASSERT_TRUE(buffer.get(e));
  expected = String("hej_1");
  ASSERT_TRUE(expected.compare(e.serialize()) == 0);
}

TEST_F(BufferTestFixture, GetPutAFew)
{
  C_Event e;
  String expected;
  String str1 = String("apa");
  String str2 = String("bepa");
  String str3 = String("test");
  
  buffer.put(C_Event(str1, 1));
  buffer.put(C_Event(str2, 2));
  buffer.put(C_Event(str3, 3));

  ASSERT_TRUE(buffer.get(e));
  expected = String("apa_1");
  ASSERT_TRUE(expected.compare(e.serialize()) == 0);

  ASSERT_TRUE(buffer.get(e));
  expected = String("bepa_2");
  ASSERT_TRUE(expected.compare(e.serialize()) == 0);

  ASSERT_TRUE(buffer.get(e));
  expected = String("test_3");
  ASSERT_TRUE(expected.compare(e.serialize()) == 0);
}

TEST_F(BufferTestFixture, Full)
{
   fillBuffer(0, buffer.capacity());
   ASSERT_TRUE(buffer.isFull());
}

TEST_F(BufferTestFixture, PutFull)
{
  C_Event e;
  String str = String("hej");
  
  fillBuffer(0, buffer.capacity());

  buffer.put(C_Event(str, 100));
  ASSERT_TRUE(buffer.get(e));
//  ASSERT_TRUE(e.serialize().compare("test_0") == 0);
   ASSERT_TRUE(String("test_0").compare(e.serialize()) == 0);
}

TEST_F(BufferTestFixture, HandleEvent)
{
  String str = String("apa");
  C_Event e;
  C_Event sendEvent = C_Event(str, 99);

  buffer.HandleEvent(sendEvent);
  ASSERT_TRUE(buffer.get(e));
  ASSERT_TRUE(String("apa_99").compare(e.serialize()) == 0);
}
} // namespace