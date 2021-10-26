#include "Arduino.h"
#include "SerialStub.h"
#include <iostream>
#include <string>

using namespace arduino_stub;

arduino_stub::byte TCCR1A = 0;  // Timer/Counter1 Control Register A
arduino_stub::byte TCCR1B = 0;  // Timer/Counter1 Control Register B
int TCNT1 = 0;   // Timer/Counter1

arduino_stub::byte TIMSK2 = 0;  // enable overflow interrupt
arduino_stub::byte TCCR2A = 0;  // Timer/Counter2 Control Register A
arduino_stub::byte TCCR2B = 0;  // Timer/Counter2 Control Register A
arduino_stub::byte OCR2A  = 0;  // compare match every 10th milli-sec @20MHz
arduino_stub::byte TCNT2  = 0;  // clear timer2

void noInterrupts(void)
{
}

void interrupts(void)
{
}

void delay(unsigned int val)
{
   (ArduinoStub::GetInstance())->IncTime(val);// .IncTime(val);
}

arduino_stub::byte digitalPinToInterrupt(arduino_stub::byte b)
{
   return b;
}

void attachInterrupt(arduino_stub::byte pin, void(*cbf)(void), InterruptMode mode)
{
   (ArduinoStub::GetInstance())->SetInterruptPin(pin);
   (ArduinoStub::GetInstance())->SetISR(cbf);

   if(mode == 0){}
}

void arduino_stub::pinMode(int pin, int m)
{
   (ArduinoStub::GetInstance())->SetMode(pin, (PinMode)m);
}

int arduino_stub::digitalRead(int pin)
{
  return (ArduinoStub::GetInstance())->DigitalRead(pin);
}

void arduino_stub::digitalWrite(int pin, int w)
{
  (ArduinoStub::GetInstance())->DigitalWrite(pin, (PinState)w);
}

void arduino_stub::analogWrite(int pin, int w)
{
  (ArduinoStub::GetInstance())->AnalogWrite(pin, w);
}

int arduino_stub::analogRead(int pin)
{
  return (ArduinoStub::GetInstance())->AnalogRead(pin);
}

unsigned long millis(void)
{
  return (unsigned long)(ArduinoStub::GetInstance())->GetTime()/1000;  //convert us to ms
}

unsigned long micros(void)
{
  return (unsigned long)(ArduinoStub::GetInstance())->GetTime();
}

ArduinoStub::ArduinoStub()
{
   Reset();
}

ArduinoStub::~ArduinoStub()
{
   arduinoStub_.reset(); // clear the weak ptr
}

std::weak_ptr<ArduinoStub> ArduinoStub::arduinoStub_;

std::shared_ptr<ArduinoStub> ArduinoStub::GetInstance()
{
   if (auto existing_instance = arduinoStub_.lock())
   {
      return existing_instance;
   }
   else
   {
      std::shared_ptr<ArduinoStub> tmp_shared(new ArduinoStub());
      arduinoStub_ = tmp_shared;
      return tmp_shared;
   }
}

void ArduinoStub::SetMode(const int pin, const PinMode m)
{
   /*try
   {
      digitalPins.at(pin).SetMode(m);
   }
   catch (const std::out_of_range& oor)
   {
      std::cerr << "Out of Range error: " << oor.what() << '\n';
   }*/
   digitalPins.at(pin).SetMode(m);
}

int ArduinoStub::GetMode(const int pin)
{
   return digitalPins.at(pin).MockGetMode();
}

void ArduinoStub::DigitalWrite(const int pin, const PinState w)
{
   digitalPins.at(pin).DigitalWrite(w);
}

int ArduinoStub::GetDigitalWrite(const int pin)
{
   return digitalPins.at(pin).MockGetDigitalWrite();
}

void ArduinoStub::AnalogWrite(const int pin, int w)
{
   digitalPins.at(pin).AnalogWrite(w);
}

int ArduinoStub::GetAnalogWrite(const int pin)
{
   return digitalPins.at(pin).MockGetAnalogWrite();
}

void ArduinoStub::SetDigitalRead(const int pin, const PinState data)
{
   digitalPins.at(pin).MockSetDigitalRead(data);
}

int ArduinoStub::DigitalRead(const int pin)
{
   return digitalPins.at(pin).DigitalRead();
}

void ArduinoStub::SetAnalogPinVoltage(const int pin, const float v)
{
  analogPins.at(pin).SetAnalogVoltage(v);
}

unsigned int ArduinoStub::AnalogRead(const int pin)
{
  return analogPins.at(pin).AnalogRead();
}

void ArduinoStub::Reset()
{
   for (auto& pin : digitalPins)
   {
      pin.DigitalWrite(PinState_Low);
      pin.SetMode(PinMode_Input);
   }

   time = 0;

   isr = NULL;
}

void ArduinoStub::IncTime(const unsigned long t)
{
  time += t;
}

void ArduinoStub::IncTimeMs(const unsigned long t)
{
  time += 1000*t;
}

unsigned long ArduinoStub::GetTime()
{
  return time;
}

void ArduinoStub::SetInterruptPin(arduino_stub::byte pin)
{
   interruptPin = pin;
}

void ArduinoStub::SetISR(void(*cbf)(void))
{
   isr = cbf;
}

void ArduinoStub::InvokeInterrupt(const unsigned int val)
{
  SetDigitalRead(interruptPin, (PinState) val);

   if (isr != NULL)
   {
      isr();
   }
}
