//
// Created by maxim on 12/05/2026.
//

#ifndef MCU_ROBOT_PRINCIPAL_RETURN_TASK_H
#define MCU_ROBOT_PRINCIPAL_RETURN_TASK_H
#include "cmsis_os.h"
#include "main.h"

typedef struct {
    int color_team;
    int color_brick_1;
    int color_brick_2;
    int color_brick_3;
    int color_brick_4;
} CommandeColors;

void StartReturnTask(void *argument);

#endif  // MCU_ROBOT_PRINCIPAL_RETURN_TASK_H
