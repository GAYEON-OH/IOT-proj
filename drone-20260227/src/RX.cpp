#include <Arduino.h>
#include "RX.h"

SoftwareSerial btSerial(10, 11); 

unsigned long last_cmd_time = 0;

void initRX() {
    btSerial.begin(9600);
    target_Roll = 0.0f;
    target_Pitch = 0.0f;
    target_Yaw = 0.0f;
    base_Throttle = 1000;
}

void readBluetooth() {
    if (btSerial.available() > 0) {
        char cmd = btSerial.read();
        last_cmd_time = millis();

        if (cmd == 'W' || cmd == 'w') target_Pitch += 1.0f;
        else if (cmd == 'S' || cmd == 's') target_Pitch -= 1.0f;
        else if (cmd == 'A' || cmd == 'a') target_Roll -= 1.0f;
        else if (cmd == 'D' || cmd == 'd') target_Roll += 1.0f;
        else if (cmd == 'T' || cmd == 't') base_Throttle += 10;
        else if (cmd == 'G' || cmd == 'g') base_Throttle -= 10;
        else if (cmd == 'X' || cmd == 'x') {
            target_Roll = 0.0f; 
            target_Pitch = 0.0f;
        }

        if (target_Pitch > 30.0f) target_Pitch = 30.0f;
        if (target_Pitch < -30.0f) target_Pitch = -30.0f;
        if (target_Roll > 30.0f) target_Roll = 30.0f;
        if (target_Roll < -30.0f) target_Roll = -30.0f;
        if (target_Yaw > 30.0f) target_Yaw = 30.0f;
        if (target_Yaw < -30.0f) target_Yaw = -30.0f;
        if (base_Throttle > 2000) base_Throttle = 2000;
        if (base_Throttle < 1000) base_Throttle = 1000;
    }

    if (millis() - last_cmd_time > 500) {
        target_Roll = 0.0f;
        target_Pitch = 0.0f;
        target_Yaw = 0.0f;
        base_Throttle = 1000;
    }
}