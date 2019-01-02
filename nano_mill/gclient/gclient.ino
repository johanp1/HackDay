// Client for parsing G-code commands sent over serial line
// controlls RC-servos
//
// By Johan Pettersson

#include <Servo.h>

typedef enum
{
  Idle,
  Moving
} state_T;

typedef struct 
{
   //config parameters
   byte spindle_speed;  // rpm
   byte cutting_feed;   // mm/minute
   byte traverse_feed;

   byte curr_feed;      // the current feed rate mm/minute
      
   int curr_x;          //[10 mico meter unit]
   int curr_y;
   int curr_z;
   
   int ref_x;
   int ref_y;
   int ref_z;

   state_T state;
} mill_T;

typedef struct
{
  int high_limit;
  int low_limit;

  Servo servo;
} servo_T;

// global variables ////////////////////////

Servo xServo;
Servo yServo;
Servo zServo;

mill_T myMill;

int x_servo_angle = 1500;

////////////////////////////////////////////


void setup() {
  myMill.state = Idle;
  myMill.traverse_feed = 100;
  myMill.cutting_feed = 1;
  myMill.curr_feed = 1;
  
	Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps

	xServo.attach(9);
	xServo.writeMicroseconds(x_servo_angle);

  Serial.setTimeout(500);
	Serial.println("Hello");
}

void loop() {
	char ser_in[20];	// for incoming serial data
  char in_len;
  
	// send data only when you receive data:
	if (Serial.available() > 0) {
		// read the incoming byte:
		in_len = Serial.readBytes(ser_in, 20);

    if (myMill.state == Idle)
    {
      parseCmdLn(ser_in, in_len);
    }
	}
	
	delay(50);                       // waits 50ms
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
  Serial.println(tmp_str);
  /////////////////////////////

  //traverse the command line looking for individual commands
  while((!done) && (i < len-1)) //len-1 because a command must be followed by a number
  {
    if (cmd_ln[i] == 'G')
    {
      handleG(cmd_ln[i+1]);

      Serial.println(myMill.curr_feed);
    }
    else if (cmd_ln[i] == 'X')
    {
      // hopefully the next few positions in cmd_ln contains our x-coordinate
      tmp_int = snipInt(cmd_ln, i+1, len);
      
      Serial.print("X: ");
      Serial.println(tmp_int);
    }
    else if (cmd_ln[i] == 'Y')
    {
      // hopefully the next few positions in cmd_ln contains our y-coordinate
      tmp_int = snipInt(cmd_ln, i+1, len);
      
      Serial.print("Y: ");
      Serial.println(tmp_int);
    }
    else if (cmd_ln[i] == 'F')
    {
      // hopefully the next few positions in cmd_ln contains our y-coordinate
      tmp_int = snipInt(cmd_ln, i+1, len);
      
      Serial.print("F: ");
      Serial.println(tmp_int);
      if (tmp_int != 0)
      {
        myMill.cutting_feed = tmp_int;
        myMill.curr_feed = myMill.cutting_feed;
      }
    }
    else if (cmd_ln[i] == 'M')
    {
      // hopefully the next few positions in cmd_ln contains our y-coordinate
      tmp_int = snipInt(cmd_ln, i+1, len);
      
      Serial.print("M: ");
      Serial.println(tmp_int);

      // debug ////////////////////
      if ((tmp_int<=2350) && (tmp_int >= 750)) 
      {
        x_servo_angle = tmp_int;
        xServo.writeMicroseconds(x_servo_angle);
      }
      //////////////////////////////
    }
    else
    {
      // throw away
    }
    
    i = i+1;
  }
  
  Serial.println("done");
}

// set the feed_rate
void handleG(char cmd)
{
  if (cmd == '1')
  {
    myMill.curr_feed = myMill.cutting_feed;
  }
  if (cmd == '0')
  {
    myMill.curr_feed = myMill.traverse_feed;
  }
}

// dig out number from a string.
// the string is assumed to start with integer 
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

