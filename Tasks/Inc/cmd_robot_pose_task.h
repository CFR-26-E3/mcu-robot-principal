#ifndef MCU_ROBOT_PRINCIPAL_CMD_POSE_TASK_H
#define MCU_ROBOT_PRINCIPAL_CMD_POSE_TASK_H

#include "cmsis_os2.h"
#include "robot_config.h"
#include "robot_types.h"

typedef struct {
} CmdRobotPoseTaskParams;

void StartCmdRobotPoseTask(void* argument);
Twist2D GetRobotCmdVel();

#endif  // MCU_ROBOT_PRINCIPAL_CMD_POSE_TASK_H
