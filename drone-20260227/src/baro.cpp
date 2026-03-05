#include <Arduino.h>
#include "baro.h"

Adafruit_BMP280 bmp;

void initBaro() {
    if (!bmp.begin(0x76)) {
        Serial.println("기압계 초기화 실패. 주소 0x76에서 BMP280을 찾을 수 없습니다.");
        while (1);
    }
    Serial.println("BMP280 기압계 초기화 완료");
}

void readBaro() {
    raw_altitude = bmp.readAltitude(1013.25); // 해수면 압력 기준으로 고도 계산
    current_altitude = raw_altitude; // 현재 고도 업데이트
}
