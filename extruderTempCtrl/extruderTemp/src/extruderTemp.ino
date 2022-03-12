 #include "controller.h"
#include "event_parser.h"
#include "receiver.h"
#include "extruder.h"

void setRefTemp(int newRef);

class SetTempFunctionoid : public ParserFunctionoid
{
  public:
    SetTempFunctionoid(PIDController& ctrl) : ParserFunctionoid{String("sp")}, controller(ctrl) {};
    void execute(String& _parsedData) {
      controller.SetRef((_parsedData.toInt()) * 10); // convert to 0.1 degrees unit
    };

  private:
    PIDController& controller;
};

class SetEnableFunctionoid : public ParserFunctionoid
{
  public:
    SetEnableFunctionoid(PIDController& ctrl) : ParserFunctionoid{String("en")}, controller(ctrl) {};
    void execute(String& _parsedData) {
      controller.SetEnable(_parsedData.toInt() > 0 ? true : false);
    };

  private:
    PIDController& controller;
};

class SetDebugFunctionoid : public ParserFunctionoid
{
  public:
    SetDebugFunctionoid(PIDController& ctrl, Extruder& ext) : ParserFunctionoid{String("debug")}, controller(ctrl), extruder(ext) {};
    void execute(String& _parsedData) {
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
SetTempFunctionoid setTempFunct;
SetEnableFunctionoid setEnableFunct{tempCtrl};
SetDebugFunctionoid setDebugFunct{tempCtrl, extruder};

void setup() {
  Serial.begin(38400);  // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(500);
  // Sets the two pins as Outputs

  pinMode(pwmPin, OUTPUT);
  pinMode(tempPin, INPUT);  // analog read pin

  analogWrite(pwmPin, 0);

  receiver.addEventListner(&ep);
  ep.AddAcceptedCmd(setTempFunct);
  ep.AddAcceptedCmd(setEnableFunct);
  ep.AddAcceptedCmd(setDebugFunct);

  tempCtrl.SetRef(1000); // reference temperature in [0.1 degrees], i.e 250 = 25 degrees

  Serial.println("setup done"); // tell server setup is done
}

void loop()
{
  int duty = 0; //0-255
  int currTemp;

  currTemp = extruder.ReadTemp();

  tempCtrl.Step(currTemp);  // temp in [0.1 degrees]
  duty = tempCtrl.GetOut();

  Serial.print("mv_");
  Serial.println((int)(currTemp) / 10);

  extruder.SetTempPwmDuty(duty);

  delay(1000); // One second delay
}

void serialEvent()
{
  receiver.scan();
}
