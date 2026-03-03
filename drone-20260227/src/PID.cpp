#include "config.h"
#include <Arduino.h>

float error = 0.0f, P_error = 0.0f, I_error = 0.0f, D_error = 0.0f;
float P_out = 0.0f, I_out = 0.0f, D_out = 0.0f;

// 각 축별 적분값 (static으로 함수 간 유지)
static float roll_int = 0.0f, pitch_int = 0.0f, yaw_int = 0.0f;
static float roll_prev = 0.0f, pitch_prev = 0.0f, yaw_prev = 0.0f;
static unsigned long last_time = 0;

void initPID() {
    roll_int = pitch_int = yaw_int = 0.0f;  // 적분값 초기화
    roll_prev = pitch_prev = yaw_prev = 0.0f; // 이전 오차 초기화
}


float calcPID_Roll(float targetRoll, float currentRoll) {
    // dt 계산 (config.h의 LOOP_TIME 기반)
    unsigned long now = micros();
    float dt = (float)(now - last_time) / 1000000.0f;
    if (dt > 0.02f) dt = DT;  // 250Hz 제한
    
    // 1. 오차 계산
    error = targetRoll - currentRoll;
    
    // 2. P(비례항)
    P_error = error;
    P_out = R_P * P_error;
    
    // 3. I(적분항) - 누적 + Windup 방지
    roll_int += error * dt;
    if (roll_int > 50.0f) roll_int = 50.0f;      // 상한
    if (roll_int < -50.0f) roll_int = -50.0f;    // 하한
    I_error = roll_int;
    I_out = R_I * I_error;
    
    // 4. D(미분항)
    if (dt > 0.0001f) {
        D_error = (error - roll_prev) / dt;
    }
    D_out = R_D * D_error;
    roll_prev = error;
    
    // 5. PID 합산 + 출력 제한
    float output = P_out + I_out + D_out;
    if (output > 500.0f) output = 500.0f;
    if (output < -500.0f) output = -500.0f;
    
    last_time = now;
    return output;
}

float calcPID_Pitch(float targetPitch, float currentPitch) {
    unsigned long now = micros();
    float dt = (float)(now - last_time) / 1000000.0f;
    if (dt > 0.02f) dt = DT;
    
    error = targetPitch - currentPitch;
    
    P_error = error;
    P_out = P_P * P_error;
    
    pitch_int += error * dt;
    if (pitch_int > 50.0f) pitch_int = 50.0f;
    if (pitch_int < -50.0f) pitch_int = -50.0f;
    I_error = pitch_int;
    I_out = P_I * I_error;
    
    if (dt > 0.0001f) {
        D_error = (error - pitch_prev) / dt;
    }
    D_out = P_D * D_error;
    pitch_prev = error;
    
    float output = P_out + I_out + D_out;
    if (output > 500.0f) output = 500.0f;
    if (output < -500.0f) output = -500.0f;
    
    last_time = now;
    return output;
}

float calcPID_Yaw(float targetYaw, float currentYaw) {
    unsigned long now = micros();
    float dt = (float)(now - last_time) / 1000000.0f;
    if (dt > 0.02f) dt = DT;
    
    error = targetYaw - currentYaw;
    
    P_error = error;
    P_out = Y_P * P_error;
    
    yaw_int += error * dt;
    if (yaw_int > 50.0f) yaw_int = 50.0f;
    if (yaw_int < -50.0f) yaw_int = -50.0f;
    I_error = yaw_int;
    I_out = Y_I * I_error;
    
    if (dt > 0.0001f) {
        D_error = (error - yaw_prev) / dt;
    }
    D_out = Y_D * D_error;
    yaw_prev = error;
    
    float output = P_out + I_out + D_out;
    if (output > 500.0f) output = 500.0f;
    if (output < -500.0f) output = -500.0f;
    
    last_time = now;
    return output;
}
