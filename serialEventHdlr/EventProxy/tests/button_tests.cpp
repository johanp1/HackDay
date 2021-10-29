#include <gtest/gtest.h>
#include "button.h"
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

class ButtonTestFixture : public testing::Test 
{  
   protected: 
   std::unique_ptr<Button> b;
   EventListnerSpy evSpy;
   std::shared_ptr<ArduinoStub> arduinoStub = ArduinoStub::GetInstance();

   void SetUp() override
   {
      arduinoStub->Reset();
      b = std::make_unique<Button>("test", PIN, 50);
      b->addEventListner(&evSpy);
   }
   
   void TearDown()
   {
      b.reset();
   }
};

TEST_F(ButtonTestFixture, Init)
{
  ASSERT_TRUE(INPUT == arduinoStub->GetMode(PIN));
  ASSERT_TRUE(LOW == b->getState());
}

TEST_F(ButtonTestFixture, ButtonNotPressed)
{
  arduinoStub->SetDigitalRead(PIN, LOW);
  
  b->scan();
  ASSERT_TRUE(LOW == b->getState());
  ASSERT_TRUE(!evSpy.newData);
  
  arduinoStub->IncTimeMs(51); //longer than debounce delay
  
  b->scan();
  ASSERT_TRUE(LOW == b->getState());
  ASSERT_TRUE(!evSpy.newData);
}

TEST_F(ButtonTestFixture, PressButtonLong)
{
  arduinoStub->SetDigitalRead(PIN, HIGH);

  b->scan();
  ASSERT_TRUE(LOW == b->getState());
  ASSERT_TRUE(!evSpy.newData);
  
  arduinoStub->IncTimeMs(51); //longer than debounce delay
  
  b->scan();
  ASSERT_TRUE(HIGH == b->getState());
  ASSERT_TRUE(evSpy.newData);
  ASSERT_TRUE(evSpy.serializedEvent.compare("test_1") == 0);
}

TEST_F(ButtonTestFixture, PressButtonShort)
{
  arduinoStub->SetDigitalRead(PIN, HIGH);

  b->scan();
  ASSERT_TRUE(LOW == b->getState());
  ASSERT_TRUE(!evSpy.newData);
    
  arduinoStub->IncTimeMs(49); //shorter than debounce delay
  
  b->scan();
  ASSERT_TRUE(LOW == b->getState());
  ASSERT_TRUE(!evSpy.newData);
}

TEST_F(ButtonTestFixture, ReleaseButton)
{
  arduinoStub->SetDigitalRead(PIN, HIGH);

  b->scan();

  arduinoStub->IncTimeMs(51); //longer than debounce delay

  b->scan();
  ASSERT_TRUE(HIGH == b->getState());

  arduinoStub->SetDigitalRead(PIN, LOW);

  b->scan();
  ASSERT_TRUE(HIGH == b->getState());
  
  arduinoStub->IncTimeMs(51); //longer than debounce delay

  b->scan();
  ASSERT_TRUE(LOW == b->getState());
}
} // namespace
