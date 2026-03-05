#ifndef PID_H
#define PID_H

#include "config.h"

void initPID();

float calcPID_Roll(float targetRoll, float currentRoll, float throttle);
float calcPID_Pitch(float targetPitch, float currentPitch, float throttle);
float calcPID_Yaw(float targetYaw, float currentYaw, float throttle);

#endif