//
// Created by maxim on 12/05/2026.
//

//
// Created by maxim on 11/05/2026.
//

#include <math.h>

#include "spread_task.h"

extern TIM_HandleTypeDef htim8;

typedef struct {
    float angle;
} CommandeServo;

CommandeServo commandes[2] = {{ANGLE_ECARTEMENT_SERRE},
                              {ANGLE_ECARTEMENT_DESSERRE}};

void StartSpreadTask(void *argument) {
    SpreadTaskArgument *params = (SpreadTaskArgument *)argument;

    ServoMotorConfig ecartementCfg = {
        .htim_pwm = &htim8,
        .channel_number = TIM_CHANNEL_6,
        .pulse_min = 0.0005f,  // 0.5ms en secondes
        .pulse_max = 0.0025f,  // 2.5ms en secondes
        .angle_max = 90.0f,
        .interrupt_mode = 0};

    init_servo_motor(&params->spread_servo, &ecartementCfg);

    set_servo_angle(&params->spread_servo, 0.0f);
    float angle = 90.0f;
    while (1) {
        osThreadFlagsWait(1, 0, osWaitForever);
        set_servo_angle(&params->spread_servo, angle);
        osDelay(500);
        // osThreadFlagsSet(*argument->, 1);
    }
}

