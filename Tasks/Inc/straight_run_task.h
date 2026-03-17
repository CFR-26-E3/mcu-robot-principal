#ifndef MCU_ROBOT_PRINCIPAL_STRAIGTH_RUN_H
#define MCU_ROBOT_PRINCIPAL_STRAIGTH_RUN_H

#include "cmsis_os2.h"
#include "dc_motor.h"
#include "main.h"

typedef struct {
    DcMotor left_motor;
    DcMotor right_motor;
} StraightRunTaskParam;

void StartStraightRunTask(void *argument);

#endif  // MCU_ROBOT_PRINCIPAL_STRAIGTH_RUN_H
