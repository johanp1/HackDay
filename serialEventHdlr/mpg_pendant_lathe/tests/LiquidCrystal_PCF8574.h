class LiquidCrystal_PCF8574
{
   public:
   LiquidCrystal_PCF8574(int i2cAddr) : i2cAddr_(i2cAddr){};

   void begin(uint8_t cols, uint8_t rows) {};
   void clear() {};
   void home() {};
   void print(const String& str) {};
   void setCursor(uint8_t col, uint8_t row) {};
   void setBacklight(uint8_t brightness) {};
   
   uint8_t i2cAddr_;
};
