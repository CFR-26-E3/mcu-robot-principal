//
// Created by maxim on 12/05/2026.
//

#ifndef MCU_ROBOT_PRINCIPAL_RETURN_TASK_H
#define MCU_ROBOT_PRINCIPAL_RETURN_TASK_H
#include "cmsis_os.h"
#include "servo_motor.h"
#include "strategy_task.h"

#define FLIP_TASK_START_FLAG 1

typedef struct {
    ServoMotor servo_return_1;
    ServoMotor servo_return_2;
    ServoMotor servo_return_3;
    ServoMotor servo_return_4;

    osThreadId_t *strategy_task;
} FlipTaskParams;

typedef struct {
    int color_team;
    int color_brick_1;
    int color_brick_2;
    int color_brick_3;
    int color_brick_4;
} CommandeColors;

void StartFlipTask(void *argument);

#endif  // MCU_ROBOT_PRINCIPAL_RETURN_TASK_H
