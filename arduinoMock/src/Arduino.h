#ifndef __ARDUINO_TEST_DOUBLE_H_
#define __ARDUINO_TEST_DOUBLE_H_
   
#include <string>
#include <array>
#include "String.h"
#include "SerialStub.h"
#include "PinMock.h"
#include "AnalogPinMock.h"
#include <memory>

typedef enum{
   InterruptMode_Change = 0,
   InterruptMode_Rising = 1
} InterruptMode;

#define CHANGE InterruptMode_Change
#define RISING InterruptMode_Rising

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5

#define CS10 0
#define CS11 1
#define CS12 2
#define CS20 0
#define CS21 1
#define CS22 2
#define OCIE2A 1
#define WGM21 1

#define ISR(X) void interruptServiceRoutine(X)
#define TIMER2_COMPA_vect void

namespace arduino_stub
{
using byte = char;

//singelton class
class ArduinoStub
{
   public:
   ~ArduinoStub();
   
   ArduinoStub(ArduinoStub&) = delete; // Copy prohibited
   void operator=(const ArduinoStub&) = delete; // Assignment prohibited
   ArduinoStub& operator=(ArduinoStub&&) = delete; // Move assignment

   static std::shared_ptr<ArduinoStub> GetInstance();

   void SetMode(const int pin, const PinMode m);
   int GetMode(const int pin);

   void DigitalWrite(const int pin, const PinState v);
   int GetDigitalWrite(const int pin);

   void AnalogWrite(const int pin, int w);
   int GetAnalogWrite(const int pin);

   void SetDigitalRead(const int pin, const PinState data);
   int DigitalRead(const int pin);

   void SetAnalogPinVoltage(const int pin, const float v);
   unsigned int AnalogRead(const int pin);
  
   void IncTimeMs(const unsigned long t);
   void IncTime(const unsigned long t);
   unsigned long GetTime();

   void SetInterruptPin(const byte pin);
   void SetISR(void(*cbf)(void));
   void InvokeInterrupt(const unsigned int val);

   void Reset();

   protected:
   ArduinoStub();

   private:
   static std::weak_ptr<ArduinoStub> arduinoStub_;
   std::array<MockDigitalPin, 9> digitalPins;
   std::array<MockAnalogPin, 4> analogPins;

   unsigned long time;
   void(*isr)(void);
   byte interruptPin;
};

void setup();
void loop();
void delay(unsigned int val);
byte digitalPinToInterrupt(byte b);
void attachInterrupt(byte pin, void(*cbf)(void), InterruptMode mode);
void noInterrupts(void);
void interrupts(void);
void pinMode(int pin, int m);
int digitalRead(int pin);
void digitalWrite(int pin, int w);
void analogWrite(int pin, int w);
int analogRead(int pin);
unsigned long millis(void);
unsigned long micros(void);

extern byte TCCR1A;  // Timer/Counter1 Control Register A
extern byte TCCR1B;  // Timer/Counter1 Control Register B
extern int  TCNT1;   // Timer/Counter1

extern byte TIMSK2;  // enable overflow interrupt
extern byte TCCR2A;  // Timer/Counter2 Control Register A
extern byte TCCR2B;  // Timer/Counter2 Control Register A
extern byte OCR2A;   // compare match every 10th milli-sec @20MHz
extern byte TCNT2;   // clear timer2

#endif /* __ARDUINO_TEST_DOUBLE_H_ */
} // end namespace arduinoMock