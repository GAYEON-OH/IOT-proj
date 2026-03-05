#include "config.h"
#include <SoftwareSerial.h>

extern SoftwareSerial btSerial;

extern float target_Roll;
extern float target_Pitch;
extern float target_Yaw;
extern int target_Alt;


void initRX();
void readBluetooth();