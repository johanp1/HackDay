// Client for parsing G-code commands sent over serial line
// controlls RC-servos
//
// By Johan Pettersson

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

int incomingByte = 0;	// for incoming serial data

void setup() {
	Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps
   
   Serial.println("Hello");
}

void loop() {

	// send data only when you receive data:
	if (Serial.available() > 0) {
		// read the incoming byte:
		incomingByte = Serial.read();

		// say what you got:
		Serial.print("I received: ");
		Serial.println(incomingByte, DEC);
	}
}