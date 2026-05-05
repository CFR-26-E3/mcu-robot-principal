#include "cmd_robot_pose_task.h"

#include <stdio.h>

#include "odometry_task.h"
#include "pid_controller.h"
#include "planar-computation.h"

static Twist2D robot_cmd_vel;
osMutexId_t robot_cmd_vel_mutex;

static PIDController distance_pid;
static PIDController angle_pid;

float ComputeRobotSpeedFromDistance(float distance) {
    return ROBOT_MIN_SPEED +
           (ROBOT_MAX_SPEED - ROBOT_MIN_SPEED) *
               (1 - expf(-distance / CHARACTERISTIC_DISTANCE));
}

float ComputeRobotAngularSpeedFromAngle(float angle) {
    if (angle >= 0) {
        return ROBOT_MIN_ANGULAR_SPEED +
               (ROBOT_MAX_ANGULAR_SPEED - ROBOT_MIN_ANGULAR_SPEED) *
                   (1 - expf(-angle / CHARACTERISTIC_ANGLE));
    } else {
        return -(ROBOT_MIN_ANGULAR_SPEED +
                 (ROBOT_MAX_ANGULAR_SPEED - ROBOT_MIN_ANGULAR_SPEED)) *
               (1 - expf(angle / CHARACTERISTIC_ANGLE));
    }
}

void StartCmdRobotPoseTask(void* argument) {
    CmdRobotPoseTaskParams* params = (CmdRobotPoseTaskParams*)(argument);

    robot_cmd_vel_mutex = osMutexNew(NULL);

    Pose2D target1 = (Pose2D){2.0f, 0.0f, 0.0f};
    Pose2D target2 = (Pose2D){0.0f, 2.0f, 0.0f};

    Pose2D targets[2] = {target1, target2};
    int target_index = 0;

    uint32_t ticks = osKernelGetTickCount();
    while (1) {
        ticks += CMD_ROBOT_POSE_TASK_PERIOD;
        osDelayUntil(ticks);

        Pose2D robot_pose = GetRobotPose();

        float distance = ComputeL2Distance(robot_pose, targets[target_index]);
        float angle = ComputeAngleToPath(robot_pose, targets[target_index]);

        float v = ComputeRobotSpeedFromDistance(distance);
        float w = ComputeRobotAngularSpeedFromAngle(angle);

        if (distance < 0.1) {
            w = 0.0f;
        }

        if (distance < TARGET_THRESHOLD) {
            v = 0.0f;

            /*w = ComputeRobotAngularSpeedFromAngle(targets[target_index].theta
            - robot_pose.theta);

            if (fabsf(targets[target_index].theta - robot_pose.theta) <
                ANGLE_THRESHOLD) {*/
            target_index++;
            if (target_index >= 2) target_index = 0;
            //}
        }

        if (osMutexAcquire(robot_cmd_vel_mutex, 10) == osOK) {
            robot_cmd_vel = (Twist2D){v, w};
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