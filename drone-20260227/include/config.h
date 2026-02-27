#ifndef CONFIG_H
#define CONFIG_H

/* MPU6050 주소 */
#define MPU6050_ADDR 0x68

/* 모터 핀 번호 */
#define PWM_FL 3
#define PWM_FR 5
#define PWM_BL 6
#define PWM_BR 9

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
float R_P = 1.0f, R_I = 0.0f, R_D = 0.0f;
float P_P = 1.0f, P_I = 0.0f, P_D = 0.0f;
float Y_P = 1.0f, Y_I = 0.0f, Y_D = 0.0f;

#endif