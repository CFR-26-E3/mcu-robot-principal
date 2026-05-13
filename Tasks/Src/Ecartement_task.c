//
// Created by maxim on 12/05/2026.
//

//
// Created by maxim on 11/05/2026.
//

#include <math.h>

#include "Strat_task.h"
#include "depose_task.h"
#include "main.h"
#include "servo_motor.h"

extern ServoMotor EcartementServo;

extern TIM_HandleTypeDef htim8;

typedef struct {
    float angle;
} CommandeServo;

CommandeServo commandes[2] = {{ANGLE_ECARTEMENT_SERRE},
                              {ANGLE_ECARTEMENT_DESSERRE}};

void StartReposeTask(void *argument) {
    ServoMotorConfig ecartementCfg = {
        .htim_pwm = &htim8,
        .channel_number = TIM_CHANNEL_6,
        .pulse_min = 0.0005f,  // 0.5ms en secondes
        .pulse_max = 0.0025f,  // 2.5ms en secondes
        .angle_max = 90.0f,
        .interrupt_mode = 0};

    init_servo_motor(&EcartementServo, &ecartementCfg);

    set_servo_angle(&EcartementServo, 0.0f);
    float angle = 90.0f;
    while (1) {
        osThreadFlagsWait(1, 0, osWaitForever);
 set_servo_angle(&EcartementServo, angle);
        osDelay(500);
        // osThreadFlagsSet(*argument->, 1);
    }
}

