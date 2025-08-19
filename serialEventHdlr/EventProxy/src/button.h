 #ifndef __C_BUTTON_H__
#define __C_BUTTON_H__

#include <Arduino.h>
#include "event_generator.h"

enum ButtonState {BUTTON_RELEASED, BUTTON_PRESSED};

class Button : public EventGenerator
{
 
 public:
   Button(const String& argName, const int argPin, const unsigned long argDebounceDelay, const bool flipped = false);

   virtual void scan(void);
   ButtonState getState();
   
    virtual ButtonState readCurrentState();
 protected:
   int pin;
   ButtonState state; // debounced buttons state
   ButtonState prevState;
   unsigned long debounceTime;
   unsigned long time;
   bool flipped_;

  //private:
};

class ButtonPullup : public Button
{
  public:
    ButtonPullup(const String& argName, const int argPin, const unsigned long argDebounceDelay, const bool flipped = false) : Button(argName, argPin, argDebounceDelay, flipped){pinMode(pin, INPUT_PULLUP); state = readCurrentState();};

    ButtonState readCurrentState() override;
};

#endif // __BUTTON_H__

