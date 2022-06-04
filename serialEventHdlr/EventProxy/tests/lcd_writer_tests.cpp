#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "lcd_writer.h"

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
   MOCK_METHOD(void, clear, (), ());
   //MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (const));
   //MOCK_METHOD(size_t, NumberOfPackets, (), (const));
};

TEST(LcdWriterTestGroup, init)
{
   MockLcd mock_lcd(0x27);

   LcdWriter<MockLcd> lcdWriter(&mock_lcd);
   lcdWriter.clear();
}