#include <Arduino.h>

#include <MPU6050.h>
#include <i2Cdev.h>
#include <Wire.h>

#include "config.h"
#include "Motor.h"
#include "IMU.h"
#include "RX.h"
#include "PID.h"
#include "Motor.h"


MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  initIMU();
  initPID();
  initMotors(); 
}

void loop() {
  // 1. 250Hz 제어 주기
  static unsigned long last_time = 0;
  unsigned long now = micros();
  if (now - last_time < LOOP_TIME) return;
  last_time = now;

  readIMU();
  calcRP();

  float target_Throttle = 0.4f;  // 40% 부양
    float target_Roll = 0.0f;      // 좌우 중립  
    float target_Pitch = 0.0f;     // 앞뒤 중립
    float target_Yaw = 0.0f;
    
    float current_Roll = Roll, current_Pitch = Pitch, current_Yaw = Yaw;
    
    float PID_Roll = calcPID_Roll(target_Roll, current_Roll);
    float PID_Pitch = calcPID_Pitch(target_Pitch, current_Pitch);
    float PID_Yaw = calcPID_Yaw(target_Yaw, current_Yaw);
    
    calcMotors(target_Throttle, PID_Roll, PID_Pitch, PID_Yaw);
}