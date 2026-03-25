#include "cmd_robot_pose_task.h"

#include <stdio.h>

#include "odometry_task.h"
#include "pid_controller.h"

static Twist2D robot_cmd_vel;
osMutexId_t robot_cmd_vel_mutex;

static PIDController distance_pid;
static PIDController angle_pid;

void StartCmdRobotPoseTask(void* argument) {
    CmdRobotPoseTaskParams* params = (CmdRobotPoseTaskParams*)(argument);

    robot_cmd_vel_mutex = osMutexNew(NULL);

    Pose2D target = (Pose2D){1.0, 0.0, 0.0};

    uint32_t ticks = osKernelGetTickCount();
    while (1) {
        ticks += CMD_ROBOT_POSE_TASK_PERIOD;
        osDelayUntil(ticks);

        Pose2D robot_pose = GetRobotPose();

        printf("x=%.3f y=%.3f t=%.2f\r\n", robot_pose.x, robot_pose.y,
               robot_pose.theta);

        if (osMutexAcquire(robot_cmd_vel_mutex, 10) == osOK) {
            robot_cmd_vel = (Twist2D){target.x - robot_pose.x, 0.0f};
            osMutexRelease(robot_cmd_vel_mutex);
        }
    }
}

Twist2D GetRobotCmdVel() {
    if (osMutexAcquire(robot_cmd_vel_mutex, 0) == osOK) {
        Twist2D robot_cmd_vel_safe = robot_cmd_vel;
        osMutexRelease(robot_cmd_vel_mutex);
        return robot_cmd_vel_safe;
    }

    return (Twist2D){0};
}