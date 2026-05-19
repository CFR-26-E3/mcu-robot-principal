#ifndef MCU_ROBOT_PRINCIPAL_CMD_POSE_TASK_H
#define MCU_ROBOT_PRINCIPAL_CMD_POSE_TASK_H

#include <stdio.h>

#include "cmsis_os2.h"
#include "detection_task.h"
#include "odometry_task.h"
#include "pid_controller.h"
#include "planar-computation.h"
#include "robot_config.h"
#include "strategy_task.h"

typedef struct {
    osThreadId_t* strategy_task;
} CmdRobotPoseTaskParams;

void StartCmdRobotPoseTask(void* argument);
Twist2D GetRobotCmdVel();
void SetPoseTarget(Pose2D i);

#endif  // MCU_ROBOT_PRINCIPAL_CMD_POSE_TASK_H
