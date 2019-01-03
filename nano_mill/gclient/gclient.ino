// Client for parsing G-code commands sent over serial line
// controlls RC-servos
//
// By Johan Pettersson

#include <Servo.h>

#define MAX_TRAVERSE_FEED 100  // default G0 feed rate, fastest possible

#define X_MAX 2000 //[10 mico meter unit]
#define X_MIN -2000
#define Y_MAX 2000
#define Y_MIN -2000
#define Z_MAX 2000
#define Z_MIN -2000
#define MIN_100MS_MOVEMENT 5  // 5 [10um] = 0.05mm
#define MIN_FEED 60

typedef enum
{
  Idle,
  Moving,
  Test
} state_T;

typedef struct 
{
   //config parameters
   byte spindle_speed;   // rpm
   
   byte cutting_feed;    // mm/minute
   byte curr_feed; // the current feed rate 10um/100ms
      
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

void setup() {
  myMill.state = Idle;
  myMill.spindle_speed = 100;
  myMill.cutting_feed = MIN_FEED;  // default cutting feed rate
  myMill.curr_feed = MIN_FEED;    // current cutting feed rate
  myMill.curr_x = 0;
  myMill.ref_x = 0;
  myMill.curr_y = 0;
  myMill.ref_y = 0;
  
	Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps

	xServo.attach(9);
	xServo.writeMicroseconds(x_servo_angle);

  Serial.setTimeout(500);
	Serial.println("Hello");

  debug_dump();
}

void loop() {
	char ser_in[20];	// for incoming serial data
  char in_len;
  long tmpD;
  int D, dD, n, dx, dy;
  bool done = 0;
  
	// send data only when you receive data:
	if (Serial.available() > 0) {
		// read the incoming byte:
		in_len = Serial.readBytes(ser_in, 20);

    parseCmdLn(ser_in, in_len);
	}
 
  if ((myMill.curr_x != myMill.ref_x) || (myMill.curr_y != myMill.ref_y))
  {
    myMill.state = Moving;
    
    // control error, distance between ref and current position
    tmpD = (long)(myMill.ref_x - myMill.curr_x) * (long)(myMill.ref_x - myMill.curr_x);
    tmpD += (long)(myMill.ref_y - myMill.curr_y) * (long)(myMill.ref_y - myMill.curr_y);
    D = (int)sqrt(tmpD);
    
    dD = myMill.curr_feed / 6;  // travel per 100ms, [mm/minut] = 100*[10um]/60*10[100ms]   
    
    // calculate number of 100ms iterations it will require to travel distance D.
    // will be rounded
    n = (D/dD + 0.5);           // number of 100ms to move distance D
    if (n == 0)                 // if distance to travel takes lesser than 100 ms
    {
      n = 1;                    // travel that distace in 100 ms anyway
    }

    Serial.print("D: ");
    Serial.println(D);
    Serial.print("n: ");
    Serial.println(n);

    // if this is the last iteration to reach target or n really was 1.xy, then set curr to target
    if (n == 1)
    {
      myMill.curr_x = myMill.ref_x;
      myMill.curr_y = myMill.ref_y;
      done = 1;
    }
    else
    {
      // calculate x and y distance to move this iteration 
      dx = abs(myMill.ref_x - myMill.curr_x)/n;
      if (myMill.curr_x < myMill.ref_x)  // do the move with correct direction
      {
        myMill.curr_x += dx;
      }
      else
      {
        myMill.curr_x -= dx;
      }
        
      dy = abs(myMill.ref_y - myMill.curr_y)/n;
      if (myMill.curr_y < myMill.ref_y)
      {
        myMill.curr_y += dy;
      }
      else
      {
        myMill.curr_y -= dy;
      }
    }
    
    //set servo angle..... based on curr_x and curr_y
    
    Serial.print("dx: ");
    Serial.println(dx);
    Serial.print("dy: ");
    Serial.println(dy);
    Serial.println("");
  }

  if (done)
  {
    myMill.state = Idle;
    Serial.println("done");
    done = 0;
  }
	
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
  Serial.print("rec: ");
  Serial.println(tmp_str);
  /////////////////////////////

  //traverse the command line looking for individual commands
  while((!done) && (i < len-1)) //len-1 because a command must be followed by a number
  {
    if (cmd_ln[i] == 'G')
    {
      handleG(cmd_ln[i+1]);
      
      Serial.print("feed: ");
      Serial.println(myMill.curr_feed);
    }
    else if (cmd_ln[i] == 'X')
    {
      // hopefully the next few positions in cmd_ln contains our x-coordinate
      tmp_int = snipInt(cmd_ln, i+1, len);

      myMill.ref_x = saturate(tmp_int, X_MAX, X_MIN);
      
      Serial.print("X: ");
      Serial.println(tmp_int);
    }
    else if (cmd_ln[i] == 'Y')
    {
      // hopefully the next few positions in cmd_ln contains our y-coordinate
      tmp_int = snipInt(cmd_ln, i+1, len);

      myMill.ref_y = saturate(tmp_int, Y_MAX, Y_MIN);
      
      Serial.print("Y: ");
      Serial.println(tmp_int);
    }
    else if (cmd_ln[i] == 'F')
    {
      // hopefully the next few positions in cmd_ln contains our y-coordinate
      tmp_int = snipInt(cmd_ln, i+1, len);
            
      if (tmp_int < MIN_FEED)
      {
        tmp_int = MIN_FEED;
      }
      
      myMill.cutting_feed = tmp_int;
      myMill.curr_feed = myMill.cutting_feed;

      Serial.print("F: ");
      Serial.println(tmp_int);
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
        myMill.state = Test;
        x_servo_angle = tmp_int;
        xServo.writeMicroseconds(x_servo_angle);
      }
      if (tmp_int == 0)
      {
        myMill.state = Idle;
      }
      //////////////////////////////
    }
    else if (cmd_ln[i] == 'D')
    {
      debug_dump(); 
    }
    else
    {
      // throw away
    }
    
    i = i+1;
  }
  
  Serial.println("done parsing cmd_ln");
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
    myMill.curr_feed = MAX_TRAVERSE_FEED;
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

int saturate(int in, int max_limit, int min_limit)
{
  int retVal = in;
  
  if (in > max_limit)
  {
    retVal = max_limit;
  }
  if (in < min_limit)
  {
    retVal = min_limit;
  }

  return retVal;
}

void debug_dump(void)
{
  Serial.print("myMill.state: ");
  Serial.println(myMill.state);
  
  Serial.print("myMill.spindle_speed: ");
  Serial.println(myMill.spindle_speed);
    
  Serial.print("myMill.cutting_feed: ");
  Serial.println(myMill.cutting_feed);
  
  Serial.print("myMill.curr_feed: ");
  Serial.println(myMill.curr_feed);
  
  Serial.print("myMill.curr_x: ");
  Serial.println(myMill.curr_x);
  
  Serial.print("myMill.ref_x: ");
  Serial.println(myMill.ref_x);
  
  Serial.print("myMill.curr_y: ");
  Serial.println(myMill.curr_y);
  
  Serial.print("myMill.ref_y: ");
  Serial.println(myMill.ref_y);
}

