#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "lcd_writer.h"
#include <Arduino.h>

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
};

TEST(LcdWriterTestGroup, clearing)
{
   MockLcd mock_lcd(0x27);
   LcdWriter<MockLcd> lcdWriter(mock_lcd, String("apa"));

   EXPECT_CALL(mock_lcd, clear());
   //lcdWriter.clear();
   lcdWriter();
}

TEST(LcdWriterTestGroup, homing)
{
   MockLcd mock_lcd(0x27);
   LcdWriter<MockLcd> lcdWriter(mock_lcd, String("apa"));

   EXPECT_CALL(mock_lcd, home());
   //lcdWriter.home();
   lcdWriter();
}

TEST(LcdWriterTestGroup, print_simple)
{
   String temp_str = String("hej");
   MockLcd mock_lcd(0x27);
   LcdWriter<MockLcd> lcdWriter(mock_lcd, String("apa"));

   EXPECT_CALL(mock_lcd, print(String("hej")));
   //lcdWriter.print(String("hej"));
   lcdWriter(temp_str);
}