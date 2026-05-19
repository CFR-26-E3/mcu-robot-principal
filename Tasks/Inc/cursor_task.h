
#ifndef MCU_ROBOT_PRINCIPAL_CURSOR_TASK_H
#define MCU_ROBOT_PRINCIPAL_CURSOR_TASK_H

#include "cmsis_os.h"
#include "main.h"
extern TIM_HandleTypeDef htim8;
void StartCurseurTask(void *argument);
#endif  // MCU_ROBOT_PRINCIPAL_CURSOR_TASK_H
