// Client for parsing G-code commands sent over serial line
// controlls RC-servos
//
// By Johan Pettersson

#include "mill.h"

#define debug_print(x)  if(debug_flag) {Serial.print(#x); Serial.print(": "); Serial.println(x);}

// global variables ////////////////////////

byte debug_flag = 1;
C_Mill mill;

void setup() {

  Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps

  Serial.setTimeout(500);

  //mill = new C_Mill;
  mill.init();

  debug_dump();
}

void loop() {
  char ser_in[20];	// for incoming serial data
  char in_len;
  
	// send data only when you receive data:
	if (Serial.available() > 0) {
		// read the incoming byte:
		in_len = Serial.readBytes(ser_in, 20);

    parseCmdLn(ser_in, in_len);
	}
 
  mill.run();
  
  delay(100);                       // waits 100ms
}

//parse command line and execute each command
void parseCmdLn(char* cmd_ln, byte len)
{
  byte i = 0;
  bool done = 0;
  int tmp_int;
  
  //temp debug ////////////////
  String tmp_str = cmd_ln;
  tmp_str.remove(len);
  debug_print(tmp_str);
  /////////////////////////////

  //traverse the command line looking for individual commands
  while((!done) && (i < len-1)) //len-1 because a command must be followed by a number
  {
    if (cmd_ln[i] == 'G')
    {
      if (cmd_ln[i+1] == '1')
      {
        mill.setLinInterCutFeed();  // set mill to move with linear interpolation at cutting feed
      }
      if (cmd_ln[i+1] == '0')
      {
        mill.setLinInterTravFeed(); // set mill to move with linear interpolation at max feed feed
      }
    }
    else if (cmd_ln[i] == 'X')
    {
      // hopefully the next few positions in cmd_ln contains our x-coordinate
      tmp_int = snipInt(cmd_ln, i+1, len);

      mill.setRefX(tmp_int);
    }
    else if (cmd_ln[i] == 'Y')
    {
      // hopefully the next few positions in cmd_ln contains our y-coordinate
      tmp_int = snipInt(cmd_ln, i+1, len);

      mill.setRefY(tmp_int);
    }
    else if (cmd_ln[i] == 'F')
    {
      // hopefully the next few positions in cmd_ln contains our y-coordinate
      tmp_int = snipInt(cmd_ln, i+1, len);
      
      mill.setCuttingFeed(tmp_int);
    }
    else if (cmd_ln[i] == 'M')
    {
      // hopefully the next few positions in cmd_ln contains our y-coordinate
      tmp_int = snipInt(cmd_ln, i+1, len);

      // debug ////////////////////
      if (tmp_int == 99) 
      {
        mill.setTestState(1);
      }
      if (tmp_int == 0)
      {
        mill.setTestState(0);
      }
      //////////////////////////////
    }
    else if (cmd_ln[i] == 'D')
    { 
      debug_flag = (cmd_ln[i+1] == '0' ? 0 : 1);
	    mill.setDebugFlag(debug_flag);
	  
	    if (debug_flag)
      {
        debug_dump();
	    }
    }
    else
    {
      // throw away
    }
    
    i = i+1;
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
    if((str[i] <= '9') && (str[i] >= '0'))
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

void debug_dump(void)
{
  mill.debug_dump();
  debug_print(debug_flag);
}

