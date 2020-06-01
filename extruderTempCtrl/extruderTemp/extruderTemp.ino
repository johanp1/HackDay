#include "controller.h"
#include "event_parser.h"
#include "receiver.h"

#define debug_print(x)   if(debug){Serial.print(#x); Serial.print(": "); Serial.println(x);}

void setRefTemp(int newRef);
void setEnable(int en);
void setDebug(int d);
int readTemp();

class SetTempFunctionoid : public ParserFunctionoid
{
  public:
  void execute(String& _parsedData) { setRefTemp(_parsedData.toInt()); };
};

class SetEnableFunctionoid : public ParserFunctionoid
{
  public:
  void execute(String& _parsedData) { setEnable(_parsedData.toInt()); };
};

class SetDebugFunctionoid : public ParserFunctionoid
{
  public:
  void execute(String& _parsedData) { setDebug(_parsedData.toInt()); };
};

// defines pins numbers
int debug;
const int pwmPin = 5;
const int tempPin = A4;
int refTemp = 1000; // reference temperature in [0.1 degrees], i.e 250 = 25 degrees
bool enable;

Receiver receiver(String("rec"));
EventParser ep;
SetTempFunctionoid setTempFunct;
SetEnableFunctionoid setEnableFunct;
SetDebugFunctionoid setDebugFunct;

PIDParameters p(2,    // K, 
               12000, // Ti, rule of thumb h/Ti = 0.1-0.3 (h=period)
               0,     // Td 
               10,    // N 
               3000,  // Tr, rule of thumb Tr = sqrt(Ti*Td)
               1);    // beta

PIDController tempCtrl(1000, p, 0, 200);

void setup() {
  String setTempCmd = String("sp");
  String enableCmd = String("en");
  String debugCmd = String("debug");

  debug = 0;
  enable = false;
  
  Serial.begin(38400);  // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(500);
  // Sets the two pins as Outputs

  pinMode(pwmPin, OUTPUT);
  pinMode(tempPin, INPUT);  // analog read pin
  
  receiver.addEventListner(&ep);
  ep.addAcceptedCmd(setTempCmd, setTempFunct);
  ep.addAcceptedCmd(enableCmd, setEnableFunct);
  ep.addAcceptedCmd(debugCmd, setDebugFunct);
   
  Serial.println("hello"); // tell server setup is done
}

void loop() 
{
  int duty = 0; //0-255
  int currTemp;

  currTemp = readTemp();

  if(enable)
  {
    duty = tempCtrl.step(currTemp, refTemp);  // temp in [0.1 degrees]
    debug_print(currTemp);
    debug_print(refTemp);
	  debug_print(duty);
	
	  Serial.print("mv_");
	  Serial.println(currTemp);
  } 
  
  analogWrite(pwmPin, duty);

  delay(1000); // One second delay
}

void setRefTemp(int newRef)
{
  refTemp = newRef*10; // convert to 0.1 degrees unit
  debug_print(refTemp);
}

void setEnable(int en)
{
  enable = (en > 0 ? true : false);
  debug_print(enable);
}

void setDebug(int d)
{
  debug = (d > 0 ? true : false);
  debug_print(debug);
}

int readTemp()
{
  int adc;
  long T, mv;

  adc = analogRead(tempPin);  // adc 0-1023, 1023 = Vref = 5V
  mv = ((long)adc*5000)/1024;       // converted to milli volt
  debug_print(adc);
  debug_print(mv);
  
  T = (2792500 - ((long)(389*mv)))/1000;  //[0.1 degrees]
  
  return T;
}

void serialEvent()
{
  receiver.scan();
}
