// Client for parsing G-code commands sent over serial line
// controlls RC-servos
//
// By Johan Pettersson

#include <Servo.h>

typedef struct 
{
   byte spindle_speed;  // rpm
   byte cutting_feed;   // mm/minute
   byte traverse_feed;  // mm/minute
   
   byte curr_x;
   byte curr_y;
   byte curr_z;
   
   byte ref_x;
   byte ref_y;
   byte ref_z;
} mill_T;

// global variables ////////////////////////

Servo xServo;
Servo yServo;
Servo zServo;

mill_T myMill;

int x_servo_angle = 1500;

////////////////////////////////////////////


void setup() {
	Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps

	xServo.attach(9);
	xServo.writeMicroseconds(x_servo_angle);
	
	Serial.println("Hello");
}

void loop() {
	int incomingByte;	// for incoming serial data

	// send data only when you receive data:
	if (Serial.available() > 0) {
		// read the incoming byte:
		incomingByte = Serial.read();

		// say what you got:
		//Serial.print("I received: ");
		Serial.print(incomingByte, DEC);
		
		if (incommingByte = '+')
		{
			x_servo_angle += 10;
			
			Serial.print((x_servo_angle & 0xff00)>>8, DEC);
			Serial.println((x_servo_angle & 0x00ff), DEC);
			
			xServo.writeMicroseconds(x_servo_angle);
		}
		if (incommingByte = '-')
		{
			x_servo_angle -= 10;
			
			Serial.print((x_servo_angle & 0xff00)>>8, DEC);
			Serial.println((x_servo_angle & 0x00ff), DEC);
			
			xServo.writeMicroseconds(x_servo_angle);
		}
	}
	
	delay(50);                       // waits 50ms
}
