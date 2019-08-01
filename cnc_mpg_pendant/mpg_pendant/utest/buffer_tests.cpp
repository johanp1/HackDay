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
      buffer.push(C_Event(s, (unsigned int)(seed+i)));
    }
  }
};

TEST(BufferTestGroup, EmptyAfterCreation)
{
  CHECK(buffer.isEmpty());
}

TEST(BufferTestGroup, NotEmpty)
{
  buffer.push(C_Event());
  CHECK(!buffer.isEmpty());
}

TEST(BufferTestGroup, PopEmpty)
{
  C_Event e;
  CHECK(!buffer.pop(e));
}


TEST(BufferTestGroup, NotEmptyThenEmpty)
{
  C_Event e;
  
  buffer.push(C_Event());
  CHECK(!buffer.isEmpty());
  CHECK(buffer.pop(e));
  CHECK(buffer.isEmpty());
}


TEST(BufferTestGroup, GetPutOneValue)
{
  C_Event e;
  string str = "hej";
  
  buffer.push(C_Event(str, 1));
  CHECK(buffer.pop(e));
  LONGS_EQUAL(1, e.getData());
  CHECK(str.compare(e.getSource()) == 0);
}

TEST(BufferTestGroup, GetPutAFew)
{
  C_Event e;
  string str1 = "1";
  string str2 = "2";
  string str3 = "3";
  
  buffer.push(C_Event(str1, 1));
  buffer.push(C_Event(str2, 2));
  buffer.push(C_Event(str3, 3));

  CHECK(buffer.pop(e));
  LONGS_EQUAL(1, e.getData());
  CHECK(str1.compare(e.getSource()) == 0);

  CHECK(buffer.pop(e));
  LONGS_EQUAL(2, e.getData());
  CHECK(str2.compare(e.getSource()) == 0);

  CHECK(buffer.pop(e));
  LONGS_EQUAL(3, e.getData());
  CHECK(str3.compare(e.getSource()) == 0);
}

TEST(BufferTestGroup, pushFull)
{
  C_Event e;
  string str = "hej";
  
  fillBuffer(0, buffer.capacity());

  buffer.push(C_Event(str, 100));
  CHECK(buffer.pop(e));
  LONGS_EQUAL(100, e.getData());
  CHECK(str.compare(e.getSource()) == 0);
  CHECK(buffer.isEmpty()); // this is a consequence of not keeping track of
  //when the buffer is full
}
