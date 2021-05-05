#include "TestHarness.h"
#include "button.h"
#include "Arduino.h"

#define PIN 3

TEST_GROUP(ButtonTestGroup)
{
   class EventListnerSpy : public EventListner{
   public:
      void enventListnerSpy()
      {
         reset();
      };
    
      void handleEvent(C_Event& e)
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

  
   std::unique_ptr<Button> b;
   EventListnerSpy evSpy;
   std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();

   void setup()
   {
      arduinoStub->Reset();
      b = std::make_unique<Button>("test", PIN, 50);
      b->addEventListner(&evSpy);
   }
  
   void teardown()
   {
      b.reset();
   }

};

TEST(ButtonTestGroup, Init)
{
  LONGS_EQUAL(INPUT, arduinoStub->GetMode(PIN));
  LONGS_EQUAL(LOW, b->getState());
}

TEST(ButtonTestGroup, ButtonNotPressed)
{
  arduinoStub->SetDigitalRead(PIN, LOW);
  
  b->scan();
  LONGS_EQUAL(LOW, b->getState());
  CHECK(!evSpy.newData);
  
  arduinoStub->IncTimeMs(51); //longer than debounce delay
  
  b->scan();
  LONGS_EQUAL(LOW, b->getState());
  CHECK(!evSpy.newData);
}

TEST(ButtonTestGroup, PressButtonLong)
{
  arduinoStub->SetDigitalRead(PIN, HIGH);

  b->scan();
  LONGS_EQUAL(LOW, b->getState());
  CHECK(!evSpy.newData);
  
  arduinoStub->IncTimeMs(51); //longer than debounce delay
  
  b->scan();
  LONGS_EQUAL(HIGH, b->getState());
  CHECK(evSpy.newData);
  CHECK(evSpy.serializedEvent.compare("test_1") == 0);
}

TEST(ButtonTestGroup, PressButtonShort)
{
  arduinoStub->SetDigitalRead(PIN, HIGH);

  b->scan();
  LONGS_EQUAL(LOW, b->getState());
  CHECK(!evSpy.newData);
    
  arduinoStub->IncTimeMs(49); //shorter than debounce delay
  
  b->scan();
  LONGS_EQUAL(LOW, b->getState());
  CHECK(!evSpy.newData);
}

TEST(ButtonTestGroup, ReleaseButton)
{
  arduinoStub->SetDigitalRead(PIN, HIGH);

  b->scan();

  arduinoStub->IncTimeMs(51); //longer than debounce delay

  b->scan();
  LONGS_EQUAL(HIGH, b->getState());

  arduinoStub->SetDigitalRead(PIN, LOW);

  b->scan();
  LONGS_EQUAL(HIGH, b->getState());
  
  arduinoStub->IncTimeMs(51); //longer than debounce delay

  b->scan();
  LONGS_EQUAL(LOW, b->getState());
}

