#include <Arduino.h>
#include <Wire.h>
#include "config.h"
#include "Motor.h"
#include "IMU.h"
#include "RX.h"
#include "PID.h"
#include "sonar.h"
#include "baro.h"


#define HOVER_THROTTLE 1500.0f


void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  initIMU();
  initRX();
  initPID();
  initMotors(); 
  initSonar();
  initBaro();
}

void loop() {
  static unsigned long last_time = 0;
  unsigned long now = micros();
  if (now - last_time < LOOP_TIME) return;
  last_time = now;

  readIMU();
  calcRP();
  readBluetooth();
  readBaro();

  float current_Roll = Roll, current_Pitch = Pitch, current_Yaw = Yaw;
    
  float front_distance = getSonarDistance();
    if (front_distance < 30.0f && target_Pitch < 0.0f) {
      target_Pitch = 15.0f;
    }

  float PID_Alt = calcPID_Altitude(target_Alt, current_altitude);
  
  float final_Throttle = HOVER_THROTTLE + PID_Alt;

  float PID_Roll = calcPID_Roll(target_Roll, current_Roll, final_Throttle);
  float PID_Pitch = calcPID_Pitch(target_Pitch, current_Pitch, final_Throttle);
  float PID_Yaw = calcPID_Yaw(target_Yaw, current_Yaw, final_Throttle);
    
  calcMotors(final_Throttle, PID_Roll, PID_Pitch, PID_Yaw);
}