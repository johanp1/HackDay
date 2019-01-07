#define MAX_TRAVERSE_FEED 1000  // default G0 feed rate, fastest possible
#define X_MAX 2000 //max/min table travel [10 mico meter unit]
#define X_MIN -2000
#define Y_MAX 2000
#define Y_MIN -2000
#define Z_MAX 2000
#define Z_MIN -2000
#define MIN_100MS_MOVEMENT 5  // 5 [10um] = 0.05mm
#define MIN_FEED 60

// defines for calculating servo control puls width
#define MAX_SERVO_ANGLE DEGRES_TO_100URAD(180)
#define MIN_SERVO_ANGLE DEGRES_TO_100URAD(0)
#define SERVO_PW_MAX_ANGLE 2300 // [us]
#define SERVO_PW_MIN_ANGLE 700  // [us]