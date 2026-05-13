//
// Created by maxim on 11/05/2026.
//

#ifndef MCU_ROBOT_PRINCIPAL_SERRAGE_TASK_H
#define MCU_ROBOT_PRINCIPAL_SERRAGE_TASK_H
#include <math.h>

#include "cmsis_os.h"
#include "robot_config.h"
#include "servo_motor.h"
enum CmdGrip { SERRE, DESSERRE };
typedef struct {
    ServoMotor GripServo;
    osThreadId_t *strategy_task;
} GripTaskParams;

void Set_grip_angle(enum CmdGrip i);
void StartGripTask(void *argument);
#endif  // MCU_ROBOT_PRINCIPAL_SERRAGE_TASK_H
