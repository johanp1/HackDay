#include "controller.h"

#define DEBUG 0
#define debug_print(x)   if(DEBUG){Serial.print(#x); Serial.print(": "); Serial.println(x);}

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

void setup() {
  Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(500);
  // Sets the two pins as Outputs

  pinMode(pwmPin, OUTPUT);
  pinMode(tempPin, INPUT);  // analog read pin
   
  Serial.println("hello"); // tell server setup is done
}

void loop() 
{
  int duty; //0-255
  int currTemp;

  currTemp = readTemp();
  updateRefTemp(&refTemp);
  duty = tempCtrl.step(currTemp, refTemp);  // temp in [0.1 degrees]
  
  debug_print(duty);
  //Serial.println(' ');
  
  analogWrite(pwmPin, duty);

  delay(1000); // One second delay
}

void updateRefTemp(int* refTemp)
{
  char in_len;
  int tmp;
  char ser_in[20];  // for incoming serial data

  if (Serial.available() > 0)
  {
    // read the incoming byte:
    in_len = Serial.readBytes(ser_in, 20);

    tmp = parseCmdLn(ser_in, in_len);
    *refTemp = tmp*10; // convert to 0.1 degrees unit
    debug_print(tmp);
  }
}

int parseCmdLn(char* cmd, byte len)
{
  String tmpStr = cmd;

  tmpStr.remove(len);
  debug_print(tmpStr);
  
  return tmpStr.toInt();
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
  debug_print(T);
  
  return T;
}
