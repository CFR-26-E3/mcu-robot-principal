#include "straight_run_task.h"

void StartStraightRunTask(void* argument) {
    StraightRunTaskParam* motors = (StraightRunTaskParam*)argument;

    set_dc_motor_pwm(&motors->left_motor, 0.2f);
    set_dc_motor_pwm(&motors->right_motor, 0.2f);

    osDelay(osKernelGetTickFreq() * 4);

    /*
    set_dc_motor_pwm(&motors->left_motor, 0.6f);
    set_dc_motor_pwm(&motors->right_motor, 0.6f);

    osDelay(osKernelGetTickFreq() * 4);    */

    set_dc_motor_pwm(&motors->left_motor, 0.0f);
    set_dc_motor_pwm(&motors->right_motor, 0.0f);

    osThreadExit();
}