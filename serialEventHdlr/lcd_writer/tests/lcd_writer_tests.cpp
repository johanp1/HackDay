#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "lcd_writer.h"
#include <Arduino.h>

using ::testing::_;
using ::testing::NiceMock;

class TestEventFunctor : public EventFunctor
{
   public:
   TestEventFunctor(String const& event_name) : EventFunctor(event_name), hasBeenCalled{false} {}; 
   
   void operator()(void)
   {
      hasBeenCalled = true;
   };

   bool hasBeenCalled;
};

class TestObserver : public Observer
{
   public:
   TestObserver() {hasBeenCalled = false;};
   void Update() override
   {
      hasBeenCalled = true;
   };

   void Reset()
   {
      hasBeenCalled = false;
   };
   
   bool hasBeenCalled;
};

class MockLcd
{
   public:
   MockLcd(uint8_t i2cAddr) : i2cAddr_(i2cAddr){};

   uint8_t i2cAddr_;

   /*void begin(uint8_t cols, uint8_t rows);
   void clear();
   void home();
   void setCursor(uint8_t col, uint8_t row);
   void cursor();
   void noCursor();
   void blink();
   void noBlink();
   void display();
   void noDisplay();
   void scrollDisplayLeft();
   void scrollDisplayRight();
   void autoscroll();
   void noAutoscroll();
   void leftToRight();
   void rightToLeft();
   void createChar(uint8_t, byte[]);
   void setBacklight(uint8_t brightness);*/
   
   MOCK_METHOD(void, begin, (uint8_t cols, uint8_t rows), ());
   MOCK_METHOD(void, clear, (), ());
   MOCK_METHOD(void, home, (), ());
   MOCK_METHOD(void, print, (const String& str), ());
   MOCK_METHOD(void, setCursor, (uint8_t col, uint8_t row), ());
   MOCK_METHOD(void, setBacklight, (uint8_t brightness), ());
};

TEST(LcdWriterTestGroup, notify_observer)
{
   TestObserver o;
   Model model;

   model.Attach(&o);

   ASSERT_FALSE(o.hasBeenCalled);
   model.SetX(0);
   ASSERT_TRUE(o.hasBeenCalled);
}

TEST(LcdWriterTestGroup, notify_observers)
{
   TestObserver o1;
   TestObserver o2;
   Model model;

   model.Attach(&o1);
   model.Attach(&o2);

   ASSERT_FALSE(o1.hasBeenCalled);
   ASSERT_FALSE(o2.hasBeenCalled);
   model.SetX(0);
   ASSERT_TRUE(o1.hasBeenCalled);
   ASSERT_TRUE(o2.hasBeenCalled);
}

TEST(LcdWriterTestGroup, detach_observer)
{
   TestObserver o;
   Model model;

   model.Attach(&o);

   ASSERT_FALSE(o.hasBeenCalled);
   model.SetX(0);
   ASSERT_TRUE(o.hasBeenCalled);
   o.Reset();
   model.Detach(&o);
   model.SetX(0);
   ASSERT_FALSE(o.hasBeenCalled);
}

TEST(LcdWriterTestGroup, detach_observers)
{
   TestObserver o1;
   TestObserver o2;
   TestObserver o3;
   Model model;

   model.Attach(&o1);
   model.Attach(&o2);
   model.Attach(&o3);

   model.SetX(0);
   ASSERT_TRUE(o1.hasBeenCalled);
   ASSERT_TRUE(o2.hasBeenCalled);
   ASSERT_TRUE(o3.hasBeenCalled);

   o1.Reset();
   o2.Reset();
   o3.Reset();

   model.Detach(&o1);
   model.Detach(&o2);
   model.SetX(0);
   ASSERT_FALSE(o1.hasBeenCalled);
   ASSERT_FALSE(o2.hasBeenCalled);
   ASSERT_TRUE(o3.hasBeenCalled);
}

TEST(LcdWriterTestGroup, updating)
{
   Model lcdModel;
   NiceMock<MockLcd> mock_lcd(0x27);
   LcdView<MockLcd> lcdView(mock_lcd, lcdModel);

   EXPECT_CALL(mock_lcd, clear());
   EXPECT_CALL(mock_lcd, setCursor(_, _));
   EXPECT_CALL(mock_lcd, print(_));
   lcdView.Update();
}

TEST(LcdWriterTestGroup, notify_update)
{
   Model lcdModel;
   NiceMock<MockLcd> mock_lcd(0x27);
   LcdView<MockLcd> lcdView(mock_lcd, lcdModel);

   EXPECT_CALL(mock_lcd, clear());
   EXPECT_CALL(mock_lcd, setCursor(_, _));
   EXPECT_CALL(mock_lcd, print(_));
   lcdModel.SetX(1.1f);
}

TEST(LcdWriterTestGroup, axis_view_set_x)
{
   Model lcdModel;
   NiceMock<MockLcd> mock_lcd(0x27);
   AxisView<MockLcd> axisView(mock_lcd, lcdModel);

   axisView.SetEnabled(true);
   EXPECT_CALL(mock_lcd, setCursor(0, 0));
   EXPECT_CALL(mock_lcd, setCursor(0, 1));
   EXPECT_CALL(mock_lcd, print(String("*x: 1.1   ")));
   EXPECT_CALL(mock_lcd, print(String(" z: 0   ")));
   lcdModel.SetX(1.1f);
}

TEST(LcdWriterTestGroup, axis_view_set_y)
{
   Model lcdModel;
   NiceMock<MockLcd> mock_lcd(0x27);
   AxisView<MockLcd> axisView(mock_lcd, lcdModel);

   axisView.SetEnabled(true);
   EXPECT_CALL(mock_lcd, setCursor(0, 0));
   EXPECT_CALL(mock_lcd, setCursor(0, 1));
   EXPECT_CALL(mock_lcd, print(String("*x: 0   ")));
   EXPECT_CALL(mock_lcd, print(String(" z: 99.99   ")));
   lcdModel.SetY(99.99f);
}

TEST(LcdWriterTestGroup, axis_view_set_active_axis)
{
   Model lcdModel;
   NiceMock<MockLcd> mock_lcd(0x27);
   AxisView<MockLcd> axisView(mock_lcd, lcdModel);

   axisView.SetEnabled(true);
   EXPECT_CALL(mock_lcd, setCursor(0, 0));
   EXPECT_CALL(mock_lcd, setCursor(0, 1));
   EXPECT_CALL(mock_lcd, print(String(" x: 0   ")));
   EXPECT_CALL(mock_lcd, print(String("*z: 0   ")));
   lcdModel.SetActiveAxis(axis_y);
}

TEST(LcdWriterTestGroup, spindle_view_enable)
{
   Model lcdModel;
   NiceMock<MockLcd> mock_lcd(0x27);
   SpindleView<MockLcd> spindleView(mock_lcd, lcdModel);

   EXPECT_CALL(mock_lcd, clear());
   EXPECT_CALL(mock_lcd, setCursor(0, 0));
   EXPECT_CALL(mock_lcd, print(String(" spindle speed:")));
   EXPECT_CALL(mock_lcd, setCursor(0, 1));
   EXPECT_CALL(mock_lcd, print(String(" 0 rpm    ")));
   spindleView.SetEnabled(true);
}
TEST(LcdWriterTestGroup, spindle_view_set_speed)
{
   Model lcdModel;
   NiceMock<MockLcd> mock_lcd(0x27);
   SpindleView<MockLcd> spindleView(mock_lcd, lcdModel);
   
   spindleView.SetEnabled(true);
   EXPECT_CALL(mock_lcd, setCursor(0, 1));
   EXPECT_CALL(mock_lcd, print(String(" 1000 rpm    ")));
   lcdModel.SetSpindleSpeed(1000);
}

TEST(LcdWriterTestGroup, enable_view)
{
   Model lcdModel;
   NiceMock<MockLcd> mock_lcd(0x27);
   LcdView<MockLcd> view(mock_lcd, lcdModel);
   
   ASSERT_FALSE(view.GetEnable());
   view.SetEnabled(true);
   ASSERT_TRUE(view.GetEnable());
}

TEST(LcdWriterTestGroup, controller_register_event)
{
    C_Event e{String("test"), String("")};
   Model lcdModel;
   NiceMock<MockLcd> mock_lcd(0x27);
   LcdView<MockLcd> view(mock_lcd, lcdModel);
   TestEventFunctor eventFunctor(String("test"));

   ASSERT_TRUE(view.GetController() != nullptr);

   view.GetController()->AddEvent(eventFunctor);
   ASSERT_FALSE(eventFunctor.hasBeenCalled);
   view.GetController()->HandleEvent(e);
   ASSERT_TRUE(eventFunctor.hasBeenCalled);
}

/*
more controller stuff. controller::myModel and controller::myView not used at all
maybe add all events in specialised controller constructor
*/