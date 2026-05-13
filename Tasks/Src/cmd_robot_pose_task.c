#include "cmd_robot_pose_task.h"

static Twist2D robot_cmd_vel;
osMutexId_t robot_cmd_vel_mutex;

static Pose2D robot_cmd_pos;
osMutexId_t robot_cmd_pos_mutex;

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

    Pose2D target = {0.0, 0.0, 0.0};
    int target_index = 0;

    uint32_t ticks = osKernelGetTickCount();
    while (1) {
        ticks += CMD_ROBOT_POSE_TASK_PERIOD;
        osDelayUntil(ticks);
        if (osMutexAcquire(robot_cmd_pos_mutex, 2) == osOK) {
            target = robot_cmd_pos;
            osMutexRelease(robot_cmd_pos_mutex);
        }
        Pose2D robot_pose = GetRobotPose();

        float distance = ComputeL2Distance(robot_pose, target);
        float angle = ComputeAngleToPath(robot_pose, target);

        float v = ComputeRobotSpeedFromDistance(distance);
        float w = ComputeRobotAngularSpeedFromAngle(angle);

        int obstacle_av_ga = 0;
        int obstacle_av_dr = 0;
        int obstacle_ar_ga = 0;

        if (distance < 0.1) {
            w = 0.0f;
        }

        if (distance < TARGET_THRESHOLD) {
            v = 0.0f;

            /*w = ComputeRobotAngularSpeedFromAngle(targets[target_index].theta
            - robot_pose.theta);

            if (fabsf(targets[target_index].theta - robot_pose.theta) <
                ANGLE_THRESHOLD) {*/

            osThreadFlagsSet(*params->strategy_task, STRAT_BIT_POSITION);
        }
        obstacle_av_ga = Get_obstacle_av_ga();
        obstacle_av_dr = Get_obstacle_av_dr();
        obstacle_ar_ga = Get_obstacle_ar_ga();
        if (obstacle_av_ga == 1) {
            v = 0.0f;
        }
        if (obstacle_ar_ga == 1) {
            v = 0.0f;
        }
        if (obstacle_av_dr == 1) {
            v = 0.0f;
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

void Set_target(Pose2D i) {
    if (osMutexAcquire(robot_cmd_pos_mutex, 2) == osOK) {
        robot_cmd_pos = i;
        osMutexRelease(robot_cmd_pos_mutex);
    }
}