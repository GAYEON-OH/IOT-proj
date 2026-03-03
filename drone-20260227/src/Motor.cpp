/* 모터 제어
PWM 신호 출력, 모터 회전 방향 설정 */
#include "Motor.h"
#include <Arduino.h>

void initMotors() {
    pinMode(PWM_FL, OUTPUT);
    pinMode(PWM_FR, OUTPUT); 
    pinMode(PWM_BL, OUTPUT);
    pinMode(PWM_BR, OUTPUT);
    
    // 모터 정지
    analogWrite(PWM_FL, 0);
    analogWrite(PWM_FR, 0);
    analogWrite(PWM_BL, 0);
    analogWrite(PWM_BR, 0);
    
    Serial.println("모터 초기화 완료");
}

void calcMotors(float throttle, float pid_roll, float pid_pitch, float pid_yaw) {
    // 기본 throttle + PID 보정
    float motor_fl = throttle - pid_roll + pid_pitch - pid_yaw;
    float motor_fr = throttle + pid_roll + pid_pitch + pid_yaw;
    float motor_bl = throttle - pid_roll - pid_pitch + pid_yaw;
    float motor_br = throttle + pid_roll - pid_pitch - pid_yaw;
    
    // 출력 범위 제한 (0~1 → PWM 변환)
    motor_fl = constrain(motor_fl, 0.0f, 1.0f) * 255;
    motor_fr = constrain(motor_fr, 0.0f, 1.0f) * 255;
    motor_bl = constrain(motor_bl, 0.0f, 1.0f) * 255;
    motor_br = constrain(motor_br, 0.0f, 1.0f) * 255;
    
    // 모터 출력
    analogWrite(PWM_FL, (int)motor_fl);
    analogWrite(PWM_FR, (int)motor_fr);
    analogWrite(PWM_BL, (int)motor_bl);
    analogWrite(PWM_BR, (int)motor_br);
}
