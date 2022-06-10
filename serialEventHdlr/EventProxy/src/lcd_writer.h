#ifndef __C_LCD_WRITER_H__
#define __C_LCD_WRITER_H__


//template <class PacketStream>
//void CreateConnection(PacketStream* stream) { ... }

template <class Lcd>
class LcdWriter {
 public:
   LcdWriter(Lcd* lcd_) : myLcd(lcd_) {myLcd->clear();};
   void clear() {myLcd->clear();};
   Lcd* myLcd;
};

#endif // __C_LCD_WRITER_H__