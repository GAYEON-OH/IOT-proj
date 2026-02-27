#define MPU6050_ADDR 0x68

#define PWM_FL 3
#define PWM_FR 5
#define PWM_BL 6
#define PWM_BR 9

#define MOTOR_MIN 1000
#define MOTOR_MAX 2000

#define LOOP_TIME 4000

float GX = 0.0f, GY = 0.0f, GZ = 0.0f;

float RP = 1.0f, RI = 0.0f, RD = 0.0f;
float PP = 1.0f, PI = 0.0f, PD = 0.0f;
float YP = 1.0f, YI = 0.0f, YD = 0.0f;