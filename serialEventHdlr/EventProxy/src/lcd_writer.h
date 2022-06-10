#ifndef __C_LCD_WRITER_H__
#define __C_LCD_WRITER_H__

#include <Arduino.h>
#include "event_parser.h"

template <class Lcd>
class LcdWriter : public CommandHandler
{
 public:
   LcdWriter(Lcd& lcd_, const String& cmd) : myLcd(lcd_), CommandHandler{cmd} {};

   void operator()()
   {
      myLcd.clear();
      myLcd.home();
      myLcd.setCursor(0, 0);
      myLcd.print("*** first line.");
   };

   void operator()(String& _parsedData)
   {
      myLcd.clear();
      myLcd.home();
      myLcd.setCursor(0, 0);
      //myLcd.print("*** first line.");
      myLcd.print(_parsedData);
   };

   private:
   Lcd& myLcd;
};

/*
template <class Lcd>
class LcdWriterChild : public LcdWriter {
   public:
   //UpdateXLcdWriter(Lcd& lcd_) : LcdWriter(lcd_, String("x")) {}; 

   void operator()(String& _parsedData)
   {};
};
*/

#endif // __C_LCD_WRITER_H__