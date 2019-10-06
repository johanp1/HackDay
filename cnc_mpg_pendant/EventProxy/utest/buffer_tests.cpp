#include "TestHarness.h"
#include "buffer.h"

TEST_GROUP(BufferTestGroup)
{
  C_Buffer buffer;
  
  void setup()
  {  
  }
  
  void teardown()
  {
    buffer.flush();
  }

  void fillBuffer(int seed, int nbr)
  {
    string s = "test";
    
    for (int i = 0; i < nbr; i++)
    {
      buffer.put(C_Event(s, (unsigned int)(seed+i)));
    }
  }
};

TEST(BufferTestGroup, EmptyAfterCreation)
{
  CHECK(buffer.isEmpty());
}

TEST(BufferTestGroup, NotEmpty)
{
  buffer.put(C_Event());
  CHECK(!buffer.isEmpty());
}

TEST(BufferTestGroup, GetEmpty)
{
  C_Event e;
  CHECK(!buffer.get(e));
}


TEST(BufferTestGroup, NotEmptyThenEmpty)
{
  C_Event e;
  
  buffer.put(C_Event());
  CHECK(!buffer.isEmpty());
  CHECK(buffer.get(e));
  CHECK(buffer.isEmpty());
}


TEST(BufferTestGroup, GetPutOneValue)
{
  C_Event e;
  string str = "hej";
  string expected;
  
  buffer.put(C_Event(str, 1));
  CHECK(buffer.get(e));
  expected = str.append("_1");
  CHECK(expected.compare(e.serialize()) == 0);
}

TEST(BufferTestGroup, GetPutAFew)
{
  C_Event e;
  string expected;
  string str1 = "apa";
  string str2 = "bepa";
  string str3 = "test";
  
  buffer.put(C_Event(str1, 1));
  buffer.put(C_Event(str2, 2));
  buffer.put(C_Event(str3, 3));

  CHECK(buffer.get(e));
  expected = str1.append("_1");
  CHECK(expected.compare(e.serialize()) == 0);

  CHECK(buffer.get(e));
  expected = str2.append("_2");
  CHECK(expected.compare(e.serialize()) == 0);

  CHECK(buffer.get(e));
  expected = str3.append("_3");
  CHECK(expected.compare(e.serialize()) == 0);
}

TEST(BufferTestGroup, Full)
{
   fillBuffer(0, buffer.capacity());
   CHECK(buffer.isFull());
}

TEST(BufferTestGroup, PutFull)
{
  C_Event e;
  string str = "hej";
  
  fillBuffer(0, buffer.capacity());

  buffer.put(C_Event(str, 100));
  CHECK(buffer.get(e));
  CHECK(e.serialize().compare("test_0") == 0);
}

TEST(BufferTestGroup, HandleEvent)
{
  string str = "apa";
  C_Event e;
  C_Event sendEvent = C_Event(str, 99);

  buffer.handleEvent(sendEvent);
  CHECK(buffer.get(e));
  CHECK(e.serialize().compare("apa_99") == 0);
}
