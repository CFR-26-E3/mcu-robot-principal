#include "cmd_robot_vel_task.h"

static PIDController left_pid_controller;
static PIDController right_pid_controller;

void StartCmdRobotVelTask(void* argument) {
    CmdRobotVelTaskParams* params = (CmdRobotVelTaskParams*)(argument);
    init_pid_controller(&left_pid_controller, KP_WHEELS_MOTOR, KI_WHEELS_MOTOR,
                        KD_WHEELS_MOTOR, ALPHA_WHEELS_MOTOR, MIN_PWM_OUTPUT,
                        MAX_PWM_OUTPUT);

    init_pid_controller(&right_pid_controller, KP_WHEELS_MOTOR, KI_WHEELS_MOTOR,
                        KD_WHEELS_MOTOR, ALPHA_WHEELS_MOTOR, MIN_PWM_OUTPUT,
                        MAX_PWM_OUTPUT);

    while (1) {
        osThreadFlagsWait(1, 0, osWaitForever);

        float left_speed =
            GetRobotCmdVel().v - GetRobotCmdVel().w * WHEELS_BASE / 2.0f;
        float right_speed =
            GetRobotCmdVel().v + GetRobotCmdVel().w * WHEELS_BASE / 2.0f;

        float left_pwm = compute_pid_controller(
            &left_pid_controller, left_speed, GetLeftWheelSpeed(), 0.01);
        float right_pwm = compute_pid_controller(
            &right_pid_controller, right_speed, GetRightWheelSpeed(), 0.01);

        set_dc_motor_pwm(&params->left_motor, left_pwm);
        set_dc_motor_pwm(&params->right_motor, right_pwm);
    }
}
