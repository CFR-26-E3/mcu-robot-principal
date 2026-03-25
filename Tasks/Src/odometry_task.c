#include "odometry_task.h"

#include <stdio.h>

#include "odometry.h"

static Pose2D robot_pose = {0.0f, 0.0f, 0.0f};
static osMutexId_t robot_pose_mutex;

static float left_wheel_speed = 0.0f;
static osMutexId_t left_wheel_speed_mutex;

static float right_wheel_speed = 0.0f;
static osMutexId_t right_wheel_speed_mutex;

void clamp_encoder_diff(int32_t *diff) {
    if (*diff > (TICKS_PER_REV_WHEELS / 2))
        *diff -= TICKS_PER_REV_WHEELS;
    else if (*diff < -(TICKS_PER_REV_WHEELS / 2))
        *diff += TICKS_PER_REV_WHEELS;
}

void StartOdometryTask(void *argument) {
    OdometryTaskParams *params = (OdometryTaskParams *)argument;

    robot_pose_mutex = osMutexNew(NULL);
    left_wheel_speed_mutex = osMutexNew(NULL);
    right_wheel_speed_mutex = osMutexNew(NULL);

    uint16_t prev_left_ticks = 0;
    uint16_t prev_right_ticks = 0;

    char buffer[100];
    char buffer_pose[100];

    uint32_t ticks = osKernelGetTickCount();
    while (1) {
        ticks += ODOMETRY_TASK_PERIOD;
        osDelayUntil(ticks);

        uint16_t left_ticks =
            (uint16_t)get_encoder_ticks(&params->left_encoder);
        uint16_t right_ticks =
            (uint16_t)get_encoder_ticks(&params->right_encoder);

        int32_t left_ticks_diff = (int32_t)left_ticks - prev_left_ticks;
        int32_t right_ticks_diff = (int32_t)right_ticks - prev_right_ticks;

        prev_left_ticks = left_ticks;
        prev_right_ticks = right_ticks;

        clamp_encoder_diff(&left_ticks_diff);
        clamp_encoder_diff(&right_ticks_diff);

        if (osMutexAcquire(left_wheel_speed_mutex, 2) == osOK) {
            left_wheel_speed =
                (float)left_ticks_diff / (float)ODOMETRY_TASK_PERIOD / 0.001f /
                (float)TICKS_PER_REV_WHEELS * 2.0 * M_PI * WHEEL_RADIUS;
            osMutexRelease(left_wheel_speed_mutex);
        }

        if (osMutexAcquire(right_wheel_speed_mutex, 2) == osOK) {
            right_wheel_speed =
                (float)right_ticks_diff / (float)ODOMETRY_TASK_PERIOD / 0.001f /
                (float)TICKS_PER_REV_WHEELS * 2.0 * M_PI * WHEEL_RADIUS;
            osMutexRelease(right_wheel_speed_mutex);
        }

        if (osMutexAcquire(robot_pose_mutex, 2) == osOK) {
            ComputePose(&robot_pose, left_ticks_diff, right_ticks_diff);
            osMutexRelease(robot_pose_mutex);
        }

        osThreadFlagsSet(params->cmd_robot_vel_task_id, 1);
    };
}

Pose2D GetRobotPose() {
    if (osMutexAcquire(robot_pose_mutex, 5) == osOK) {
        Pose2D robot_pose_safe = robot_pose;
        osMutexRelease(robot_pose_mutex);
        return robot_pose_safe;
    }

    return (Pose2D){0};
}

float GetLeftWheelSpeed() {
    if (osMutexAcquire(left_wheel_speed_mutex, 5) == osOK) {
        float left_wheel_speed_safe = left_wheel_speed;
        osMutexRelease(left_wheel_speed_mutex);
        return left_wheel_speed_safe;
    }

    return (float)left_wheel_speed;
}

float GetRightWheelSpeed() {
    if (osMutexAcquire(right_wheel_speed_mutex, 5) == osOK) {
        float right_wheel_speed_safe = right_wheel_speed;
        osMutexRelease(right_wheel_speed_mutex);
        return right_wheel_speed;
    }

    return (float)right_wheel_speed;
}