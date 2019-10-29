#define debug_print(x)   Serial.print(#x); Serial.print(": "); Serial.println(x);

// defines pins numbers
const int stepPinEW = 3;
const int dirPinEW = 4;
const int stepPinNS = 6;
const int dirPinNS = 7;

typedef struct
{
  String name;
  long stepsPerCycle;
  long totalNbrSteps;
  int dir;
  int stepPin;
  int dirPin;
} stepper_Class;

int cycleCnt;

stepper_Class stepperNS;
stepper_Class stepperEW;
  
void setup() {
  Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(500);
  // Sets the two pins as Outputs
  pinMode(stepPinEW, OUTPUT);
  pinMode(dirPinEW, OUTPUT);
  pinMode(stepPinNS, OUTPUT);
  pinMode(dirPinNS, OUTPUT);

  Serial.println("hello"); // tell server setup is done
  
  cycleCnt = 0;

  stepperNS.name = "NS";
  stepperNS.stepsPerCycle = 0;
  stepperNS.totalNbrSteps = 0;
  stepperNS.dir = LOW;
  stepperNS.stepPin = stepPinNS;
  stepperNS.dirPin = dirPinNS;

  stepperEW.name = "EW";
  stepperEW.stepsPerCycle = 0;
  stepperEW.totalNbrSteps = 0;
  stepperEW.dir = LOW;
  stepperEW.stepPin = stepPinEW;
  stepperEW.dirPin = dirPinEW;
}

void loop() {
  char ser_in[20];  // for incoming serial data
  char in_len;

  // send data only when you receive data:
  if ((Serial.available() > 0) && (cycleCnt == 0))
  {
    // read the incoming byte:
    in_len = Serial.readBytesUntil('\n', ser_in, 20);

    parseCmdLn(ser_in, in_len);

    if (stepperNS.totalNbrSteps == 0)
    {
      stepperNS.stepsPerCycle = 0;
      stepperEW.stepsPerCycle = stepperEW.totalNbrSteps;
      
      cycleCnt = 1;
    }
    else  if (stepperEW.totalNbrSteps == 0)
    {
      stepperNS.stepsPerCycle = stepperNS.totalNbrSteps;
      stepperEW.stepsPerCycle = 0;
      
      cycleCnt = 1;
    }
    else if ((stepperNS.totalNbrSteps / stepperEW.totalNbrSteps == 1) || (stepperEW.totalNbrSteps / stepperNS.totalNbrSteps == 1))
    {
      stepperNS.stepsPerCycle = stepperNS.totalNbrSteps;
      stepperEW.stepsPerCycle = stepperEW.totalNbrSteps;
      cycleCnt = 1;
    }
    else if (stepperNS.totalNbrSteps >= stepperEW.totalNbrSteps)
    { 
      stepperNS.stepsPerCycle = stepperEW.totalNbrSteps;
	  
      stepperEW.stepsPerCycle = (stepperEW.totalNbrSteps * stepperEW.totalNbrSteps) / stepperNS.totalNbrSteps;
      
      cycleCnt = stepperNS.totalNbrSteps / stepperEW.totalNbrSteps;
    } 
    else
    {
      stepperEW.stepsPerCycle = stepperNS.totalNbrSteps;
	  
      stepperNS.stepsPerCycle = (stepperNS.totalNbrSteps*stepperNS.totalNbrSteps) / stepperEW.totalNbrSteps;
      
      cycleCnt = stepperEW.totalNbrSteps / stepperNS.totalNbrSteps;
    }

    debug_print(cycleCnt);
    debug_print_stepper(&stepperEW);
    debug_print_stepper(&stepperNS);
  }

  if (cycleCnt != 0)
  {
    doSteps(&stepperEW);
    doSteps(&stepperNS);
    
    cycleCnt--;

    debug_print(cycleCnt);
  }
  
  delay(10);
}

void doSteps(stepper_Class *stepper)
{
  digitalWrite(stepper->dirPin, stepper->dir); // Enables the motor to move in a particular direction

  for (int x = 0; x < stepper->stepsPerCycle; x++)
  {
    digitalWrite(stepper->stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepper->stepPin, LOW);
    delayMicroseconds(500);
  }
}

void debug_print_stepper(stepper_Class *stepper)
{
  debug_print(stepper->name);
  debug_print(stepper->stepsPerCycle);
  debug_print(stepper->totalNbrSteps);
  debug_print(stepper->dir);
  debug_print(stepper->stepPin);
  debug_print(stepper->dirPin);
}

//parse command line and execute each command
void parseCmdLn(char* cmd_ln, byte len)
{
  byte i = 0;
  bool done = 0;

  int x = 0;
  int y = 0;

  //temp debug ////////////////
  String tmp_str = cmd_ln;
  tmp_str.remove(len);
  debug_print(tmp_str);
  /////////////////////////////

stepperNS.totalNbrSteps = 0;
stepperEW.totalNbrSteps = 0;

  //traverse the command line looking for individual commands
  while ((!done) && (i < len - 1)) //len-1 because a command must be followed by a number
  {
    if (cmd_ln[i] == 'N')
    {
      // hopefully the next few positions in cmd_ln contains our x-coordinate
      stepperNS.totalNbrSteps = snipInt(cmd_ln, i + 1, len);
      stepperNS.dir = LOW;
    }
    else if (cmd_ln[i] == 'S')
    {
      // hopefully the next few positions in cmd_ln contains our x-coordinate
      stepperNS.totalNbrSteps = snipInt(cmd_ln, i + 1, len);
      stepperNS.dir = HIGH;
    }
    else if (cmd_ln[i] == 'E')
    {
      // hopefully the next few positions in cmd_ln contains our y-coordinate
      stepperEW.totalNbrSteps = snipInt(cmd_ln, i + 1, len);
      stepperEW.dir = LOW;
    }
    else if (cmd_ln[i] == 'W')
    {
      // hopefully the next few positions in cmd_ln contains our y-coordinate
      stepperEW.totalNbrSteps = snipInt(cmd_ln, i + 1, len); 
      stepperEW.dir = HIGH;
    }
    else
    {
      // throw away
    }

    i = i + 1;
  }
}

// dig out number from a string.
// the string is assumed to start with an integer
// if string does not contain integer, 0 is returned
int snipInt(char* str, byte pos, byte len)
{
  int retVal = 0;
  bool is_neg = 0;
  bool done = 0;
  String subStr;
  byte local_pos = pos;
  byte i = 0;

  if (str[local_pos] == '-')
  {
    is_neg = 1;
    local_pos += 1;
  }

  i = local_pos;
  while ((!done) && (i < len))
  {
    if ((str[i] <= '9') && (str[i] >= '0'))
    {
      subStr.concat(str[i]);
    }
    else
    {
      done = 1;
    }

    i++;
  }

  retVal = subStr.toInt();
  if ((retVal != 0) && is_neg)
  {
    retVal = -retVal;
  }

  return retVal;
}
