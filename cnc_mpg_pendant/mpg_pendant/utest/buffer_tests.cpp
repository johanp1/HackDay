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
    string s = "";
    
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
  
  buffer.put(C_Event(str, 1));
  CHECK(buffer.get(e));
  LONGS_EQUAL(1, e.getData());
  CHECK(str.compare(e.getSource()) == 0);
}

TEST(BufferTestGroup, GetPutAFew)
{
  C_Event e;
  string str1 = "1";
  string str2 = "2";
  string str3 = "3";
  
  buffer.put(C_Event(str1, 1));
  buffer.put(C_Event(str2, 2));
  buffer.put(C_Event(str3, 3));

  CHECK(buffer.get(e));
  LONGS_EQUAL(1, e.getData());
  CHECK(str1.compare(e.getSource()) == 0);

  CHECK(buffer.get(e));
  LONGS_EQUAL(2, e.getData());
  CHECK(str2.compare(e.getSource()) == 0);

  CHECK(buffer.get(e));
  LONGS_EQUAL(3, e.getData());
  CHECK(str3.compare(e.getSource()) == 0);
}

TEST(BufferTestGroup, PutFull)
{
  C_Event e;
  string str = "hej";
  
  fillBuffer(0, buffer.capacity());

  buffer.put(C_Event(str, 100));
  CHECK(buffer.get(e));
  LONGS_EQUAL(100, e.getData());
  CHECK(str.compare(e.getSource()) == 0);
  CHECK(buffer.isEmpty()); // this is a consequence of not keeping track of
  //when the buffer is full
}

TEST(BufferTestGroup, HandleEvent)
{
  string str = "apa";
  C_Event e;
  C_Event sendEvent = C_Event(str, 99);

  buffer.handleEvent(sendEvent);
  CHECK(buffer.get(e));
  LONGS_EQUAL(99, e.getData());
  CHECK(e.getSource().compare(str) == 0);
}
