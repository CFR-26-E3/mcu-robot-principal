#include "cmd_robot_vel_task.h"

static PIDController left_pid_controller;
static PIDController right_pid_controller;

static float sign(float val) {
    if (val < 0)
        return -1.0f;
    else
        return 1.0f;
}

static float min(float a, float b) { return a < b ? a : b; }
static float max(float a, float b) { return a > b ? a : b; }

void StartCmdRobotVelTask(void* argument) {
    CmdRobotVelTaskParams* params = (CmdRobotVelTaskParams*)(argument);

    init_pid_controller(&left_pid_controller, KP_WHEELS_MOTOR, KI_WHEELS_MOTOR,
                        KD_WHEELS_MOTOR, ALPHA_WHEELS_MOTOR, MIN_PWM_OUTPUT,
                        MAX_PWM_OUTPUT);

    init_pid_controller(&right_pid_controller, KP_WHEELS_MOTOR, KI_WHEELS_MOTOR,
                        KD_WHEELS_MOTOR, ALPHA_WHEELS_MOTOR, MIN_PWM_OUTPUT,
                        MAX_PWM_OUTPUT);

    float v_a = 0;
    float w_a = 0;
    float v_filt = 0;
    float w_filt = 0;

    while (1) {
        osThreadFlagsWait(1, 0, 10);

        Twist2D twist_cmd = GetRobotCmdVel();
        float v_speed_error = twist_cmd.v - v_filt;
        float w_speed_error = twist_cmd.w - w_filt;

        float v_a_lim = sqrtf(1.5f * ROBOT_JERK * fabsf(v_speed_error));
        float w_a_lim = sqrtf(1.5f * ROBOT_ANGULAR_JERK * fabsf(w_speed_error));

        float v_a_ref =
            sign(v_speed_error) * min(v_a_lim, ROBOT_MAX_ACCELERATION);
        float w_a_ref =
            sign(w_speed_error) * min(w_a_lim, ROBOT_MAX_ANGULAR_ACCELERATION);

        float v_a_diff = v_a_ref - v_a;
        float w_a_diff = w_a_ref - w_a;

        v_a_diff = max(min(v_a_diff, ROBOT_JERK * 0.01f), -ROBOT_JERK * 0.01f);
        w_a_diff = max(min(w_a_diff, ROBOT_ANGULAR_JERK * 0.01f),
                       -ROBOT_ANGULAR_JERK * 0.01f);

        v_a += v_a_diff;
        w_a += w_a_diff;

        v_filt += v_a * 0.01f;
        w_filt += w_a * 0.01f;

        float left_speed_cmd = v_filt - w_filt * WHEELS_BASE / 2.0f;
        float right_speed_cmd = v_filt + w_filt * WHEELS_BASE / 2.0f;

        float left_pwm = compute_pid_controller(
            &left_pid_controller, left_speed_cmd, GetLeftWheelSpeed(), 0.01f);

        float right_pwm =
            compute_pid_controller(&right_pid_controller, right_speed_cmd,
                                   GetRightWheelSpeed(), 0.01f);

        set_dc_motor_pwm(&params->left_motor, left_pwm);
        set_dc_motor_pwm(&params->right_motor, right_pwm);
    }
}