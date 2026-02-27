#include <Arduino.h>

#include <MPU6050.h>
#include <i2Cdev.h>
#include <Wire.h>

MPU6050 mpu;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    mpu.initialize();
}