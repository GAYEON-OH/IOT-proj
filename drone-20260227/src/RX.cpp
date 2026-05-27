#include <Arduino.h>
#include "RX.h"

SoftwareSerial btSerial(10, 11); 

unsigned long last_cmd_time = 0;

float target_Roll = 0.0f;
float target_Pitch = 0.0f;
float target_Yaw = 0.0f;
float target_Alt = 0;

void initRX() {
    btSerial.begin(9600);
}

void readBluetooth() {
    if (btSerial.available() > 0) {
        char cmd = btSerial.read();
        last_cmd_time = millis();

        if (cmd == 'W' || cmd == 'w') target_Pitch += 1.0f;
        else if (cmd == 'S' || cmd == 's') target_Pitch -= 1.0f;
        else if (cmd == 'A' || cmd == 'a') target_Roll -= 1.0f;
        else if (cmd == 'D' || cmd == 'd') target_Roll += 1.0f;
        else if (cmd == 'T' || cmd == 't') target_Alt += 1;
        else if (cmd == 'G' || cmd == 'g') target_Alt -= 1;
        else if (cmd == 'Q' || cmd == 'q') target_Yaw -= 1.0f;
        else if (cmd == 'E' || cmd == 'e') target_Yaw += 1.0f;
        else if (cmd == 'X' || cmd == 'x') {
            target_Roll = 0.0f; 
            target_Pitch = 0.0f;
            target_Yaw = 0.0f;
        }

        if (target_Pitch > 30.0f) target_Pitch = 30.0f;
        if (target_Pitch < -30.0f) target_Pitch = -30.0f;
        if (target_Roll > 30.0f) target_Roll = 30.0f;
        if (target_Roll < -30.0f) target_Roll = -30.0f;
        if (target_Yaw > 30.0f) target_Yaw = 30.0f;
        if (target_Yaw < -30.0f) target_Yaw = -30.0f;
        if (target_Alt > 100) target_Alt = 100;
        if (target_Alt < 0) target_Alt = 0;
    }

    if (millis() - last_cmd_time > 500) {
        target_Roll = 0.0f;
        target_Pitch = 0.0f;
        target_Yaw = 0.0f;
    }
}