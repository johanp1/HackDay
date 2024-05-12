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
      evSpy.reset();
      arduinoStub->Reset();
      b = std::make_unique<Button>("test", PIN, 50);
      b->addEventListner(&evSpy);
   }
   
   void TearDown()
   {
      b.reset();
   }
};

TEST_F(ButtonTestFixture, testInit)
{
  ASSERT_TRUE(INPUT == arduinoStub->GetMode(PIN));
  ASSERT_TRUE(BUTTON_RELEASED == b->getState());
}

TEST_F(ButtonTestFixture, testButtonNotPressed)
{
  arduinoStub->SetDigitalRead(PIN, LOW);
  
  b->scan();
  ASSERT_TRUE(BUTTON_RELEASED == b->getState());
  ASSERT_TRUE(!evSpy.newData);
  
  arduinoStub->IncTimeMs(51); //longer than debounce delay
  
  b->scan();
  ASSERT_TRUE(BUTTON_RELEASED == b->getState());
  ASSERT_TRUE(!evSpy.newData);
}

TEST_F(ButtonTestFixture, testPressButtonLong)
{
  arduinoStub->SetDigitalRead(PIN, HIGH);

  b->scan();
  ASSERT_TRUE(BUTTON_RELEASED == b->getState());
  ASSERT_TRUE(!evSpy.newData);
  
  arduinoStub->IncTimeMs(51); //longer than debounce delay
  
  b->scan();
  ASSERT_TRUE(BUTTON_PRESSED == b->getState());
  ASSERT_TRUE(evSpy.newData);
  ASSERT_TRUE(evSpy.serializedEvent.compare("test_1") == 0);
}

TEST_F(ButtonTestFixture, testPressButtonShort)
{
  arduinoStub->SetDigitalRead(PIN, HIGH);

  b->scan();
  ASSERT_TRUE(BUTTON_RELEASED == b->getState());
  ASSERT_TRUE(!evSpy.newData);
    
  arduinoStub->IncTimeMs(49); //shorter than debounce delay
  
  b->scan();
  ASSERT_TRUE(BUTTON_RELEASED == b->getState());
  ASSERT_TRUE(!evSpy.newData);
}

TEST_F(ButtonTestFixture, testReleaseButton)
{
  arduinoStub->SetDigitalRead(PIN, HIGH);

  b->scan();

  arduinoStub->IncTimeMs(51); //longer than debounce delay

  b->scan();
  ASSERT_TRUE(BUTTON_PRESSED == b->getState());

  arduinoStub->SetDigitalRead(PIN, LOW);

  b->scan();
  ASSERT_TRUE(BUTTON_PRESSED == b->getState());
  
  arduinoStub->IncTimeMs(51); //longer than debounce delay

  b->scan();
  ASSERT_TRUE(BUTTON_RELEASED == b->getState());
}

TEST_F(ButtonTestFixture, testInitPullup)
{
   constexpr int pin = 1;
   arduinoStub->SetDigitalRead(pin, HIGH);

   b = std::make_unique<ButtonPullup>("pull", pin, 50);
   ASSERT_TRUE(INPUT_PULLUP == arduinoStub->GetMode(pin));
   ASSERT_TRUE(BUTTON_RELEASED == b->getState());
}

TEST_F(ButtonTestFixture, testPullup)
{
   constexpr int pin = 1;
   arduinoStub->SetDigitalRead(pin, HIGH);
   b = std::make_unique<ButtonPullup>("pull", pin, 50);
  
   b->scan();
   ASSERT_TRUE(b->getState() == BUTTON_RELEASED);

   arduinoStub->SetDigitalRead(pin, LOW);
   b->scan();
   ASSERT_TRUE(BUTTON_RELEASED == b->getState());
   arduinoStub->IncTimeMs(51); //longer than debounce delay
   b->scan();
   ASSERT_TRUE(b->getState() == BUTTON_PRESSED);
}

} // namespace
