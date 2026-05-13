//
// Created by maxim on 11/05/2026.
//

#ifndef MCU_ROBOT_PRINCIPAL_SERRAGE_TASK_H
#define MCU_ROBOT_PRINCIPAL_SERRAGE_TASK_H
#include "cmsis_os.h"
#include <math.h>
#include "strategy_task.h"
#include "main.h"
#include "robot_config.h"
#include "servo_motor.h"

void StartSerrageTask(void *argument);
#endif  // MCU_ROBOT_PRINCIPAL_SERRAGE_TASK_H
