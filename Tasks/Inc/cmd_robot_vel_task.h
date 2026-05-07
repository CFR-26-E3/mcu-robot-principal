#ifndef MCU_ROBOT_PRINCIPAL_CMD_VEL_TASK_H
#define MCU_ROBOT_PRINCIPAL_CMD_VEL_TASK_H

#include <stdio.h>

#include "cmd_robot_pose_task.h"
#include "dc_motor.h"
#include "odometry_task.h"
#include "pid_controller.h"

typedef struct {
    DcMotor left_motor;
    DcMotor right_motor;
} CmdRobotVelTaskParams;

void StartCmdRobotVelTask(void* argument);

#endif  // MCU_ROBOT_PRINCIPAL_CMD_VEL_TASK_H
