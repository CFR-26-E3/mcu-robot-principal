#include "cmd_robot_pose_task.h"

#include "main.h"

static Twist2D robot_cmd_vel;
osMutexId_t robot_cmd_vel_mutex;

static Pose2D target;
osMutexId_t pose_target_mutex;

static Pose2D prev_target;

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
    pose_target_mutex = osMutexNew(NULL);

    uint32_t ticks = osKernelGetTickCount();
    while (1) {
        ticks += CMD_ROBOT_POSE_TASK_PERIOD;
        osDelayUntil(ticks);

        Pose2D robot_pose = GetRobotPose();
        float distance = 0.0f;
        float angle = 0.0f;

        if (osMutexAcquire(pose_target_mutex, 10) == osOK) {
            distance = ComputeL2Distance(robot_pose, target);
            angle = ComputeAngleToPath(robot_pose, target);
            osMutexRelease(pose_target_mutex);
        }

        float v = ComputeRobotSpeedFromDistance(distance);
        float w = ComputeRobotAngularSpeedFromAngle(angle);

        if (!pose2d_are_equals(&prev_target, &target)) {
            if (fabs(angle) > ANGLE_THRESHOLD) {
                v = 0.0f;
            } else {
                prev_target = target;
            }
        }

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

        if (GetDistanceCapteurUSAvDr() < 0.3f || GetDistanceCapteurUSAvGa() < 0.3f) {
            v = 0.0f;
            w = 0.0f;
        }

        if (HAL_GPIO_ReadPin(TIRETTE_GPIO_Port, TIRETTE_Pin) == GPIO_PIN_RESET) {
            v = 0.0f;
            w = 0.0f;
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

void SetPoseTarget(Pose2D i) {
    if (osMutexAcquire(pose_target_mutex, 10) == osOK) {
        target = i;
        osMutexRelease(pose_target_mutex);
    }
}