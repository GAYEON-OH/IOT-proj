#include <Arduino.h>

#include <MPU6050.h>
#include <i2Cdev.h>
#include <Wire.h>

#include "config.h"
#include "Motor.h"
#include "IMU.h"
#include "RX.h"
#include "PID.h"

MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  initIMU();
}

void loop() {
  float current_Roll = Roll, current_Pitch = Pitch, current_Yaw = Yaw;
  float target_Roll = ((float)RX_roll - 1500.0f) * (MAX_ROLL_ANGLE / 500.0f);
  float target_Pitch = ((float)RX_pitch - 1500.0f) * (MAX_PITCH_ANGLE / 500.0f);
  float target_Yaw = ((float)RX_yaw - 1500.0f) * (MAX_YAW_ANGLE / 500.0f);

  float PID_Roll = calcPID_Roll(target_Roll, current_Roll);
  float PID_Pitch = calcPID_Pitch(target_Pitch, current_Pitch);
  float PID_Yaw = calcPID_Yaw(target_Yaw, current_Yaw);
}