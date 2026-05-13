//
// Created by maxim on 12/05/2026.
//

#ifndef MCU_ROBOT_PRINCIPAL_ECARTEMENT_TASK_H
#define MCU_ROBOT_PRINCIPAL_ECARTEMENT_TASK_H
#include "cmsis_os.h"
#include "robot_config.h"
#include "servo_motor.h"
enum CmdSpread { ECARTE, RAPPROCHE };
typedef struct {
    ServoMotor SpreadServo;
    osThreadId_t *strategy_task;
} SpreadTaskParams;
void Set_spread_angle(enum CmdSpread i);
void StartEcartementTask(void *argument);
#endif  // MCU_ROBOT_PRINCIPAL_ECARTEMENT_TASK_H
