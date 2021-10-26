#ifndef __ARDUINO_ANALOG_PIN_MOCK_H_
#define __ARDUINO_ANALOG_PIN_MOCK_H_

#include <cmath>

class MockAnalogPin  // the context class in state pattern
{
public:
   MockAnalogPin(unsigned const char resolution_ = 10, float reference_voltage_ = 5.0) : resolution(resolution_), reference_voltage(reference_voltage_) {analog_voltage = 0.0;};
   ~MockAnalogPin() {};

   unsigned int AnalogRead(void)
   {
      float a = pow(2.0f, (float)resolution) - 1;
      return (unsigned int)(a*analog_voltage/reference_voltage);
   };

   void SetAnalogVoltage(float const v_)
   {
      analog_voltage = v_ <= reference_voltage ? v_ : reference_voltage;
   };

   void SetResolution(unsigned const char resolution_)
   {
      resolution = resolution_;
   };

private:
   float analog_voltage;
   unsigned char resolution;
   float reference_voltage;
};

#endif /* __ARDUINO_ANALOG_PIN_MOCK_H_ */