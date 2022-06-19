#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "lcd_writer.h"
#include <Arduino.h>

using ::testing::_;
using ::testing::NiceMock;

class MockLcd
{
   public:
   MockLcd(uint8_t i2cAddr_) : i2cAddr(i2cAddr_){};

   uint8_t i2cAddr;

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

/*
TEST(LcdWriterTestGroup, init)
{
   Model lcdModel;
   MockLcd mock_lcd(0x27);
   EXPECT_CALL(mock_lcd, begin(16, 2));
   EXPECT_CALL(mock_lcd, setBacklight(200));

   LcdView<MockLcd> lcdView(mock_lcd, lcdModel);
}*/

TEST(LcdWriterTestGroup, updating)
{
   Model lcdModel;
   NiceMock<MockLcd> mock_lcd(0x27);
   LcdView<MockLcd> lcdView(mock_lcd, lcdModel);

   EXPECT_CALL(mock_lcd, clear());
   EXPECT_CALL(mock_lcd, setCursor(_, _));
   EXPECT_CALL(mock_lcd, print(_));
   lcdView.Draw();
}

TEST(LcdWriterTestGroup, observer_update)
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

   EXPECT_CALL(mock_lcd, setCursor(0, 0));
   EXPECT_CALL(mock_lcd, setCursor(0, 1));
   EXPECT_CALL(mock_lcd, print(String("*x: 1.1")));
   EXPECT_CALL(mock_lcd, print(String(" y: 0")));
   lcdModel.SetX(1.1f);
}

TEST(LcdWriterTestGroup, axis_view_set_y)
{
   Model lcdModel;
   NiceMock<MockLcd> mock_lcd(0x27);
   AxisView<MockLcd> axisView(mock_lcd, lcdModel);

   EXPECT_CALL(mock_lcd, setCursor(0, 0));
   EXPECT_CALL(mock_lcd, setCursor(0, 1));
   EXPECT_CALL(mock_lcd, print(String("*x: 0")));
   EXPECT_CALL(mock_lcd, print(String(" y: 99.99")));
   lcdModel.SetY(99.99f);
}

TEST(LcdWriterTestGroup, axis_view_set_active_axis)
{
   Model lcdModel;
   NiceMock<MockLcd> mock_lcd(0x27);
   AxisView<MockLcd> axisView(mock_lcd, lcdModel);

   EXPECT_CALL(mock_lcd, setCursor(0, 0));
   EXPECT_CALL(mock_lcd, setCursor(0, 1));
   EXPECT_CALL(mock_lcd, print(String(" x: 0")));
   EXPECT_CALL(mock_lcd, print(String("*y: 0")));
   lcdModel.SetActiveAxis(axis_y);
}

TEST(LcdWriterTestGroup, spindle_view_set_speed)
{
   Model lcdModel;
   NiceMock<MockLcd> mock_lcd(0x27);
   SpindleView<MockLcd> spindleView(mock_lcd, lcdModel);

   EXPECT_CALL(mock_lcd, setCursor(0, 0));
   EXPECT_CALL(mock_lcd, setCursor(0, 1));
   EXPECT_CALL(mock_lcd, print(String(" spindle speed:")));
   EXPECT_CALL(mock_lcd, print(String(" 1000 rpm")));
   lcdModel.SetSpindleSpeed(1000);
}

TEST(LcdWriterTestGroup, lcd_writer_init)
{
   MockLcd mock_lcd(0x27);

   EXPECT_CALL(mock_lcd, begin(16, 2));
   EXPECT_CALL(mock_lcd, setBacklight(200));
   LcdWriter<MockLcd> lcdWriter(mock_lcd);
}

TEST(LcdWriterTestGroup, lcd_writer_set_x)
{
   NiceMock<MockLcd> mock_lcd(0x27);
   LcdWriter<MockLcd> lcdWriter(mock_lcd);

   EXPECT_CALL(mock_lcd, setCursor(0, 0));
   EXPECT_CALL(mock_lcd, setCursor(0, 1));
   EXPECT_CALL(mock_lcd, print(String("*x: 10.9")));
   EXPECT_CALL(mock_lcd, print(String(" y: 0")));
   lcdWriter.SetX(10.9f);
}

using ::testing::InSequence;

TEST(LcdWriterTestGroup, lcd_writer_set_spindle_view)
{
   NiceMock<MockLcd> mock_lcd(0x27);
   LcdWriter<MockLcd> lcdWriter(mock_lcd);

   {
      InSequence seq;
      EXPECT_CALL(mock_lcd, setCursor(0, 0));
      EXPECT_CALL(mock_lcd, print(String(" spindle speed:")));
      EXPECT_CALL(mock_lcd, setCursor(0, 1));
      EXPECT_CALL(mock_lcd, print(String(" 0 rpm")));
   }
   lcdWriter.SetSpindleView();
}

TEST(LcdWriterTestGroup, lcd_writer_set_axis_view)
{
   NiceMock<MockLcd> mock_lcd(0x27);
   LcdWriter<MockLcd> lcdWriter(mock_lcd);

   {
      InSequence seq;
      EXPECT_CALL(mock_lcd, setCursor(0, 0));
      EXPECT_CALL(mock_lcd, print(String("*x: 0")));
      EXPECT_CALL(mock_lcd, setCursor(0, 1));
      EXPECT_CALL(mock_lcd, print(String(" y: 0")));
   }
   lcdWriter.SetAxisView();
}
