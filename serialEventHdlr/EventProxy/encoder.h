 #ifndef __C_ROTARY_ENCODER_H__
#define __C_ROTARY_ENCODER_H__

#include <Arduino.h>
#include "event_generator.h"

class RotaryEncoder : public EventGenerator{
    /*
      wraps encoder setup and update functions in a class

      !!! NOTE : user must call the encoders update method from an
      interrupt function himself! i.e. user must attach an interrupt to the
      encoder pin A and call the encoder update method from within the
      interrupt

      uses Arduino pull-ups on A & B channel outputs
      turning on the pull-ups saves having to hook up resistors
      to the A & B channel outputs

      // ------------------------------------------------------------------------------------------------
      // Example usage :
      // ------------------------------------------------------------------------------------------------
          #include "Encoder.h"

          Encoder encoder(2, 4);

          void setup() {
              attachInterrupt(0, doEncoder, CHANGE);
              Serial.begin (115200);
              Serial.println("start");
          }

          void loop(){
              // do some stuff here - the joy of interrupts is that they take care of themselves
          }

          void doEncoder(){
              encoder.update();
              Serial.println( encoder.getPosition() );
          }
      // ------------------------------------------------------------------------------------------------
      // Example usage end
      // ------------------------------------------------------------------------------------------------
    */
  public:

    // constructor : sets pins as inputs and turns on pullup resistors

    RotaryEncoder( const String& argName, int argClkPin, int argDtPin);
	~RotaryEncoder() {};
	
    // call this from your interrupt function
    void update();
    int getPosition();
    void clearPosition();
	void scan(void);

  private:

    String name;
    int position;
    int clkPin;  // clock pin
    int dtPin;   // direction pin
};

#endif // __ENCODER_H__
