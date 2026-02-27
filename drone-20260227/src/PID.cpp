/* PID 제어 
오차 파악, PID 계산, Moto 파일로 전달 */

#include <Arduino.h>
#include "PID.h"

float calcPID_Roll(float targetRoll, float currentRoll) {   
    error = targetRoll - currentRoll;
    P_error = error;
    I_error += error * DT;
    D_error = (error - P_error) / DT;

    P_out = R_P * P_error;
    I_out = R_I * I_error;
    D_out = R_D * D_error;

    return P_out + I_out + D_out;
}

float calcPID_Pitch(float targetPitch, float currentPitch) {
    error = targetPitch - currentPitch;
    P_error = error;
    I_error += error * DT;
    D_error = (error - P_error) / DT;

    P_out = P_P * P_error;
    I_out = P_I * I_error;
    D_out = P_D * D_error;

    return P_out + I_out + D_out;
}

float calcPID_Yaw(float targetYaw, float currentYaw) {
    error = targetYaw - currentYaw;
    P_error = error;
