#ifndef CONFIG_H
#define CONFIG_H

/* MPU6050 주소 */
#define MPU6050_ADDR 0x68

/* 모터 핀 번호 */
#define PWM_FL 3
#define PWM_FR 5
#define PWM_BL 6
#define PWM_BR 9

#define TRIG_PIN 12
#define ECHO_PIN 13

/* 모터 최소/최대 펄스 폭 (마이크로초) */
#define MOTOR_MIN 1000
#define MOTOR_MAX 2000

#define MAX_ROLL_ANGLE 30.0f
#define MAX_PITCH_ANGLE 30.0f
#define MAX_YAW_ANGLE 180.0f

/* PID 제어 주기, 250HZ, dt = 4000 / 1000000, 0.004초 */
#define LOOP_TIME 4000
#define DT 0.004f

/* 가속도계, 자이로 센서 값 */
float AX_offset = 0.0f, AY_offset = 0.0f, AZ_offset = 0.0f;
float GX_offset = 0.0f, GY_offset = 0.0f, GZ_offset = 0.0f;

/* Roll, Pitch, Yaw / P(비례), I(적분), D(미분) */
extern float R_P, R_I, R_D;
extern float P_P, P_I, P_D;
extern float Y_P, Y_I, Y_D;

#endif