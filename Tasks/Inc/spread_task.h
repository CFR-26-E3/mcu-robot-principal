//
// Created by maxim on 12/05/2026.
//

#ifndef MCU_ROBOT_PRINCIPAL_ECARTEMENT_TASK_H
#define MCU_ROBOT_PRINCIPAL_ECARTEMENT_TASK_H
#include "cmsis_os.h"
#include "main.h"
#include "main.h"
#include "servo_motor.h"
#include "strategy_task.h"
enum Commande { SERRE, DESSERRE };

typedef struct SpreadTaskArgument {
    ServoMotor spread_servo;
} SpreadTaskArgument;

void StartEcartementTask(void *argument);
#endif  // MCU_ROBOT_PRINCIPAL_ECARTEMENT_TASK_H
