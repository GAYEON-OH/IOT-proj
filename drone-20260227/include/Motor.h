#ifndef MOTOR_H
#define MOTOR_H

void initMotors();
void calcMotors(float throttle, float pid_roll, float pid_pitch, float pid_yaw);

#endif

