#include "config.h"

float error = 0.0f, P_error = 0.0f, I_error = 0.0f, D_error = 0.0f;
float P_out = 0.0f, I_out = 0.0f, D_out = 0.0f;

<<<<<<< Updated upstream
void initPID(){
    
}
float calcPID_Roll(float targetRoll, float currentRoll) {
}

float calcPID_Pitch(float targetPitch, float currentPitch) {
}

float calcPID_Yaw(float targetYaw, float currentYaw) {
}

float calcPID_Altitude(float targetAltitude, float currentAltitude) {
}
=======
float calcPID_Roll(float targetRoll, float currentRoll, float throttle);
float calcPID_Pitch(float targetPitch, float currentPitch, float throttle);
float calcPID_Yaw(float targetYaw, float currentYaw, float throttle);
float calcPID_Altitude(float target_Alt, float current_Alt);

#endif
>>>>>>> Stashed changes
