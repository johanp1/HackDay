 #ifndef __C_ROTARY_ENCODER_H__
#define __C_ROTARY_ENCODER_H__

#include "event_generator.h"

class C_RotaryEncoder : public C_EventGenerator{
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

    C_RotaryEncoder( const String& argName, int8_t argClkPin, int8_t argDtPin) : C_EventGenerator(argName), clkPin ( argClkPin), dtPin( argDtPin ) 
    {
      // set pin a and b to be input
      pinMode(clkPin, INPUT);
      pinMode(dtPin, INPUT);
      // and turn on pull-up resistors
      digitalWrite(clkPin, HIGH);
      digitalWrite(dtPin, HIGH);
    };

    // call this from your interrupt function

    void update () 
    {
      if (digitalRead(clkPin))
      {
         digitalRead(dtPin) ? position++ : position--;
      }
      else 
      {
         digitalRead(dtPin) ? position-- : position++;
      }
      generateEvent(position);
    };

    // returns current position

    int getPosition ()
    {
      return position;
    };

    // set the position value

    void setPosition ( const long int p)
    {
      position = p;
    };

  private:

    String name;
    int position;
    int8_t clkPin;  // clock pin
    int8_t dtPin;   // direction pin
};

#endif // __ENCODER_H__
