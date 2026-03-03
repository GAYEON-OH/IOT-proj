/* 수신기 제어
외부 인터럽트, 핀 체인지 인터럽트, 명령 기록 */

#include <Arduino.h>
#include "RX.h"

void initRX() {
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(A0), calcRoll, CHANGE);
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(A1), calcPitch, CHANGE);
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(A2), calcYaw, CHANGE);
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(A3), calcThrottle, CHANGE);
}

void calcRoll() {
    static unsigned long crntTime;
    if (digitalRead(A0) == HIGH) {
        crntTime = micros();
    } else {
        RX_roll = (unsigned long)(micros() - crntTime);
    }
}

void calcPitch() {
    static unsigned long crntTime;
    if (digitalRead(A1) == HIGH) {
        crntTime = micros();
    } else {
        RX_pitch = (unsigned long)(micros() - crntTime);
    }
}

void calcYaw() {
    static unsigned long crntTime;
    if (digitalRead(A2) == HIGH) {
        crntTime = micros();
    } else {
        RX_yaw = (unsigned long)(micros() - crntTime);
    }
}

void calcThrottle() {
    static unsigned long crntTime;
    if (digitalRead(A3) == HIGH) {
        crntTime = micros();
    } else {
        RX_throttle = (unsigned long)(micros() - crntTime);
    }
}