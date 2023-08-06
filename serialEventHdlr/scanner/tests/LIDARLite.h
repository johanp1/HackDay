/* Test double 
 * intended use, when building scanner.ino */

#ifndef __C_LIDARLite_CTRL_H__
#define __C_LIDARLite_CTRL_H__

#include <Arduino.h>

class LIDARLite
{
  public:
      LIDARLite(){};
      void begin(int = 0, bool = false){};
      void configure(int = 0){};
      void setI2Caddr(char, char){};
      void reset(){};
      int distance(bool = true){return 0;};
      void write(char, char){};
      void read(char, int, byte*, bool, char){};
      void correlationRecordToSerial(char = '\n', int = 256){};
};

#endif
