#include <iostream>
#include <array>

class LiquidCrystal_PCF8574
{
   public:
   LiquidCrystal_PCF8574(int i2cAddr) : i2cAddr_(i2cAddr){};

   void begin(uint8_t cols, uint8_t rows) {};
   void clear() {};
   void home() {};
   void print(const String& str) {printBuffer[current_row_] = str;};
   void setCursor(uint8_t col, uint8_t row) {current_row_ = row;};
   void setBacklight(uint8_t brightness) {};
   
   String& getRow(uint8_t row) {return printBuffer[row];};

   private:
   uint8_t i2cAddr_;
   uint8_t current_row_ = 0;

   std::array<String, 2> printBuffer;
};
