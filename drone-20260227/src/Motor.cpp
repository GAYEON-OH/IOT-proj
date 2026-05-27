/* 모터 제어
PWM 신호 출력, 모터 회전 방향 설정 */
#include "Motor.h"
#include <Arduino.h>
#include "config.h"
#include <Servo.h>

Servo motorFL, motorFR, motorBL, motorBR;

void initMotors() {

    motorFL.attach(PWM_FL);
    motorFR.attach(PWM_FR);
    motorBL.attach(PWM_BL);
    motorBR.attach(PWM_BR);

    
    motorFL.writeMicroseconds(1000);
    motorFR.writeMicroseconds(1000);
    motorBL.writeMicroseconds(1000);
    motorBR.writeMicroseconds(1000);

    delay(2000); 
    
    
    Serial.println("모터 초기화 완료");
}

void calcMotors(float throttle, float pid_roll, float pid_pitch, float pid_yaw) {
    /* 기본 throttle + PID 보정 */
    float motor_fl = throttle - pid_roll + pid_pitch - pid_yaw;
    float motor_fr = throttle + pid_roll + pid_pitch + pid_yaw;
    float motor_bl = throttle - pid_roll - pid_pitch + pid_yaw;
    float motor_br = throttle + pid_roll - pid_pitch - pid_yaw;
    
    int out_fl = (int)constrain(motor_fl, 1000, 2000);
    int out_fr = (int)constrain(motor_fr, 1000, 2000);
    int out_bl = (int)constrain(motor_bl, 1000, 2000);
    int out_br = (int)constrain(motor_br, 1000, 2000);

    /* 모터에 최종 PWM 신호 출력 (마이크로초 단위 직접 전송) */
    motorFL.writeMicroseconds(out_fl);
    motorFR.writeMicroseconds(out_fr);
    motorBL.writeMicroseconds(out_bl);
    motorBR.writeMicroseconds(out_br);
}
