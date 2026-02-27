#include <Arduino.h>

#include <MPU6050.h>
#include <i2Cdev.h>
#include <Wire.h>

#include "IMU.h"

MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  initIMU();
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}