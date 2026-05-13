//
// Created by maxim on 11/05/2026.
//

#ifndef MCU_ROBOT_PRINCIPAL_ASCENSEUR_TASK_H
#define MCU_ROBOT_PRINCIPAL_ASCENSEUR_TASK_H
#include <math.h>

#include "cmsis_os.h"
#include "dc_motor.h"
#include "encoder.h"
#include "pid_controller.h"
#include "robot_config.h"
typedef struct {
    DcMotor motor_levage;
    Encoder encoder_levage;
    osThreadId_t *strategy_task;
} LiftTaskParams;

void StartLiftTask(void *argument);
#endif  // MCU_ROBOT_PRINCIPAL_ASCENSEUR_TASK_H
