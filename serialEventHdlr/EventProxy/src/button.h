 #ifndef __C_BUTTON_H__
#define __C_BUTTON_H__

#include <Arduino.h>
#include "event_generator.h"

enum ButtonState {BUTTON_RELEASED, BUTTON_PRESSED};

class Button : public EventGenerator
{
 
 public:
   Button(const String& argName, const int argPin, const unsigned long argDebounceDelay);

   virtual void scan(void);
   ButtonState getState();
   
    virtual ButtonState readCurrentState() {return (unsigned int)digitalRead(pin) == LOW ? BUTTON_RELEASED : BUTTON_PRESSED;};
 protected:
   int pin;
   ButtonState state; // debounced buttons state
   ButtonState prevState;
   unsigned long debounceTime;
   unsigned long time;

  //private:
};

class ButtonPullup : public Button
{
  public:
    ButtonPullup(const String& argName, const int argPin, const unsigned long argDebounceDelay) : Button(argName, argPin, argDebounceDelay){pinMode(pin, INPUT_PULLUP); state = readCurrentState();};

  //private:

    ButtonState readCurrentState() override {return (unsigned int)digitalRead(pin) == LOW ? BUTTON_PRESSED : BUTTON_RELEASED;};
};

#endif // __BUTTON_H__

