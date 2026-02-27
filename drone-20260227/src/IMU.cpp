/* IMU 제어
Raw Data 로드, calibration, 상보 필터 */

#include <Arduino.h>

#include "IMU.h"


void initIMU() {
    Wire.begin();
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x6B);  /* PWR_MGMT_1 레지스터 */
    Wire.write(0x00);  /* 장치 활성화 */
    Wire.endTransmission(true);

    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x1B);  /* GYRO_CONFIG 레지스터 */
    Wire.write(0x08);  /* 자이로 센서 감도 ±500°/s */
    Wire.endTransmission(true);

    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x1C);  /* ACCEL_CONFIG 레지스터 */
    Wire.write(0x08);  /* 가속도계 감도 ±4g */
    Wire.endTransmission(true);

    for (int i = 0; i < 2000; i++) {
        readIMU();
        GX_offset += GX;
        GY_offset += GY;
        GZ_offset += GZ;
        delay(3);
    }
    GX_offset /= 2000;
    GY_offset /= 2000;
    GZ_offset /= 2000;
}

void readIMU() {
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x3B);  /* 가속도 X축 */
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050_ADDR, 14, true);  /* 가속도계와 자이로 센서 데이터 요청 */
    /* 비트 시프트, 비트 논리합 / 8비트 2개 -> 16비트 1개 결합*/
    AX = Wire.read() << 8 | Wire.read();
    AY = Wire.read() << 8 | Wire.read();
    AZ = Wire.read() << 8 | Wire.read();
    Wire.read(); Wire.read();  /* 온도 데이터 버림 */
    GX = Wire.read() << 8 | Wire.read();
    GY = Wire.read() << 8 | Wire.read();
    GZ = Wire.read() << 8 | Wire.read();
}

void calcAg() {
    float A_Roll = atan2(AY, AZ) * 180 / PI;
    float A_Pitch = atan2(-AX, sqrt((float)AY * (float)AY + (float)AZ * (float)AZ)) * 180 / PI;
    float Gx = ((float)GX - GX_offset) / 65.5f; float Gy = ((float)GY - GY_offset) / 65.5f; float Gz = ((float)GZ - GZ_offset) / 65.5f;
    Roll = 0.998f * (Roll + Gx * DT) + 0.002f * A_Roll;
    Pitch = 0.998f * (Pitch + Gy * DT) + 0.002f * A_Pitch;
}
