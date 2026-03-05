/* 초음파 센서
장애물 감지, 거리 측정 */

#include <Arduino.h>
#include "sonar.h"

float sonar_distance = 0.0f;

void initSonar() {
    /* 초음파 센서 핀 설정 */
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    Serial.println("초음파 센서 초기화 완료");
}

float getSonarDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 3000); // 최대 3ms 대기 (약 50cm 거리)
    if (duration == 0) {
        sonar_distance = 100.0f; // 최대 거리로 간주 (3ms 이상 응답 없으면)
    }
    else {
        sonar_distance = (duration / 2.0f) * 0.0343f; // cm 단위
    }

    return sonar_distance;
}