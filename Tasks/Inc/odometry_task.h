#ifndef MCU_ROBOT_PRINCIPAL_ODOMETRY_TASK_H
#define MCU_ROBOT_PRINCIPAL_ODOMETRY_TASK_H

#include <math.h>
#include "cmsis_os2.h"
#include "encoder.h"
#include "odometry.h"
#include "robot_config.h"
#include "robot_types.h"
#include <stdio.h>
#include "odometry.h"

typedef struct {
    Encoder left_encoder;
    Encoder right_encoder;
    osThreadId_t *cmd_robot_vel_task_id;

    UART_HandleTypeDef *huart;
} OdometryTaskParams;

void StartOdometryTask(void *argument);

Pose2D GetRobotPose();
float GetLeftWheelSpeed();
float GetRightWheelSpeed();

#endif  // MCU_ROBOT_PRINCIPAL_ODOMETRY_TASK_H
