//
// Created by maxim on 11/05/2026.
//

#include <math.h>

#include "Strat_task.h"
#include "depose_task.h"
#include "main.h"
#include "robot_config.h"
#include "servo_motor.h"

extern ServoMotor SerrageServo;

extern TIM_HandleTypeDef htim8;

static float angle_impose_180 = 100.0f;
static osMutexId_t angle_impose_180_mutex;
void StartReposeTask(void *argument) {
    ServoMotorConfig serrageCfg = {.htim_pwm = &htim8,
                                   .channel_number = TIM_CHANNEL_1,
                                   .pulse_min = 0.0005f,  // 0.5ms en secondes
                                   .pulse_max = 0.0025f,  // 2.5ms en secondes
                                   .angle_max = 180.0f,
                                   .interrupt_mode = 0};

    init_servo_motor(&SerrageServo, &serrageCfg);

    set_servo_angle(&SerrageServo, 100.0f);
    float angle = 90.0f;
    while (1) {
        osThreadFlagsWait(1, 0, osWaitForever);

        if (osMutexAcquire(angle_impose_180_mutex, 2) == osOK) {
            angle = angle_impose_180;
            osMutexRelease(angle_impose_180_mutex);
        }
        set_servo_angle(&SerrageServo, angle);
        osDelay(500);
        // osThreadFlagsSet(*argument->, 1);
    }
}

float Get_angle_impose_180() {
    if (osMutexAcquire(angle_impose_180_mutex, 5) == osOK) {
        float angle_impose_180_safe = angle_impose_180;
        osMutexRelease(angle_impose_180_mutex);
        return angle_impose_180_safe;
    }
    return 0.0f;
}
