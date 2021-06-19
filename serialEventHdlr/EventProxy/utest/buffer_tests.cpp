#include "TestHarness.h"
#include "buffer.h"

TEST_GROUP(BufferTestGroup)
{
  Buffer buffer;
  
  void setup()
  {  
  }
  
  void teardown()
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
  String str = String("hej");
  String expected;
  
  buffer.put(C_Event(str, 1));
  CHECK(buffer.get(e));
  expected = String("hej_1");
  CHECK(expected.compare(e.serialize()) == 0);
}

TEST(BufferTestGroup, GetPutAFew)
{
  C_Event e;
  String expected;
  String str1 = String("apa");
  String str2 = String("bepa");
  String str3 = String("test");
  
  buffer.put(C_Event(str1, 1));
  buffer.put(C_Event(str2, 2));
  buffer.put(C_Event(str3, 3));

  CHECK(buffer.get(e));
  expected = String("apa_1");
  CHECK(expected.compare(e.serialize()) == 0);

  CHECK(buffer.get(e));
  expected = String("bepa_2");
  CHECK(expected.compare(e.serialize()) == 0);

  CHECK(buffer.get(e));
  expected = String("test_3");
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
  String str = String("hej");
  
  fillBuffer(0, buffer.capacity());

  buffer.put(C_Event(str, 100));
  CHECK(buffer.get(e));
  CHECK(e.serialize().compare("test_0") == 0);
}

TEST(BufferTestGroup, HandleEvent)
{
  String str = String("apa");
  C_Event e;
  C_Event sendEvent = C_Event(str, 99);

  buffer.HandleEvent(sendEvent);
  CHECK(buffer.get(e));
  CHECK(e.serialize().compare("apa_99") == 0);
}
