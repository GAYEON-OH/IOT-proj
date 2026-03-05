#include <Arduino.h>
#include <Wire.h>
#include "config.h"
#include "Motor.h"
#include "IMU.h"
#include "RX.h"
#include "PID.h"
#include "sonar.h"

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  initIMU();
  initRX();
  initPID();
  initMotors(); 
  initSonar();
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
  float front_distance = getSonarDistance();
  if (front_distance < 30.0f && target_Pitch < 0.0f) {
    target_Pitch = 15.0f; /* 장애물 감지(30cm) 시 브레이크 */
  }
  float PID_Roll = calcPID_Roll(target_Roll, current_Roll);
  float PID_Pitch = calcPID_Pitch(target_Pitch, current_Pitch);
  float PID_Yaw = calcPID_Yaw(target_Yaw, current_Yaw);
    
  calcMotors(base_Throttle, PID_Roll, PID_Pitch, PID_Yaw);
}