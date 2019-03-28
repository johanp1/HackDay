 #ifndef __C_BUTTON_H__
#define __C_BUTTON_H__


class C_Button {
 
   public:

    // constructor 
   C_Button(int argPin, long argDebounceDelay) 
   {
      prevState = LOW;
      pin = argPin;
      time = 0;
      debounceTime = argDebounceDelay;
      
      pinMode(pin, INPUT);
   };


   // returns debounced button state
   int scan(void)
   {
      int currState = digitalRead(pin); // read pin
      //Serial.print("curr_state: ");
      //Serial.println(currState);
      if (currState != prevState)
      {
        //Serial.print("new state?");
         // reset the debouncing timer
         time = millis();
      }

      if ((millis() - time) > debounceTime) {
         // take the new reading since debounce timer elapsed
         if (currState != state) 
         {
          //Serial.print("accept");
            state = currState;
         }
      }
      
      prevState = currState;
      
      return state;
   };


   private:
 
   int pin;
   int state; // debounced buttons tate
   int prevState; // previuos read button state
   unsigned long debounceTime;
   unsigned long time;
};

#endif // __BUTTON_H__

