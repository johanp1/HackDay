#include "src/controller.h"
#include "event_parser.h"
#include "receiver.h"
#include "src/extruder.h"

void setRefTemp(int newRef);

class SetTempCommandHandler : public CommandHandler
{
   public:
   SetTempCommandHandler() : CommandHandler{String("sp")} {}; 

   void operator()(String& _parsedData)
   {
	  setRefTemp(_parsedData.toInt());
   };
};

class SetEnableCommandHandler : public CommandHandler
{
   public:
   SetEnableCommandHandler(PIDController& ctrl) : CommandHandler{String("en")}, controller(ctrl) {}; 

   void operator()(String& _parsedData)
   {
	  controller.SetEnable(_parsedData.toInt() > 0 ? true : false);
   };
   
   private:
    PIDController& controller;
};

class SetDebugCommandHandler : public CommandHandler
{
   public:
   SetDebugCommandHandler(PIDController& ctrl, Extruder& ext) : CommandHandler{String("debug")}, controller(ctrl), extruder(ext) {}; 

   void operator()(String& _parsedData)
   {
	  controller.SetDebug(_parsedData.toInt() > 0 ? true : false);
      extruder.SetDebug(_parsedData.toInt() > 0 ? true : false);
   };
   
   private:
    PIDController& controller;
	Extruder& extruder;
};

// defines pins numbers
const int pwmPin = 5;
const int tempPin = A4;
int refTemp = 1000; // reference temperature in [0.1 degrees], i.e 250 = 25 degrees

PIDParameters p(2,    // K,
                12000, // Ti, rule of thumb h/Ti = 0.1-0.3 (h=period)
                0,     // Td
                10,    // N
                3000,  // Tr, rule of thumb Tr = sqrt(Ti*Td)
                1);    // beta

PIDController tempCtrl(1000, p, 0, 200);
Extruder extruder(tempPin, pwmPin);
Receiver receiver(String("rec"));
EventParser ep;
SetTempCommandHandler setTempHandler;
SetEnableCommandHandler setEnableHandler{tempCtrl};
SetDebugCommandHandler setDebugHandler{tempCtrl, extruder};

void setup() {
  Serial.begin(38400);  // opens serial port, sets data rate to 38400 bps
  Serial.setTimeout(500);
  // Sets the two pins as Outputs

  pinMode(pwmPin, OUTPUT);
  pinMode(tempPin, INPUT);  // analog read pin

  analogWrite(pwmPin, 0);

  receiver.addEventListner(&ep);
  ep.AddAcceptedCmd(setTempHandler);
  ep.AddAcceptedCmd(setEnableHandler);
  ep.AddAcceptedCmd(setDebugHandler);

  Serial.println("setup done"); // tell server setup is done
}

void loop()
{
  int duty = 0; //0-255
  int currTemp;

  currTemp = extruder.ReadTemp();

  duty = tempCtrl.Step(currTemp, refTemp);  // temp in [0.1 degrees]

  Serial.print("mv_");
  Serial.println((int)(currTemp/10));

  extruder.SetTempPwmDuty(duty);

  delay(1000); // One second delay
}

void setRefTemp(int newRef)
{
  refTemp = newRef * 10; // convert to 0.1 degrees unit
}

void serialEvent()
{
  receiver.scan();
}

