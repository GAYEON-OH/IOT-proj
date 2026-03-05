#include <Arduino.h>
#include <Wire.h>
#include "config.h"
#include "Motor.h"
#include "IMU.h"
#include "RX.h"
#include "PID.h"

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  initIMU();
  initRX();
  initPID();
  initMotors(); 
}

void loop() {
  static unsigned long last_time = 0;
  unsigned long now = micros();
  if (now - last_time < LOOP_TIME) return;
  last_time = now;

  readIMU();
  calcRP();
  readBluetooth();
    
  float current_Roll = Roll, current_Pitch = Pitch, current_Yaw = Yaw;
    
  float PID_Roll = calcPID_Roll(target_Roll, current_Roll);
  float PID_Pitch = calcPID_Pitch(target_Pitch, current_Pitch);
  float PID_Yaw = calcPID_Yaw(target_Yaw, current_Yaw);
    
  calcMotors(base_Throttle, PID_Roll, PID_Pitch, PID_Yaw);
}