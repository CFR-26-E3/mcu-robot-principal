#include "servo_motor.h"

void init_servo_motor(ServoMotor* servo, ServoMotorConfig* cfg) {
    servo->htim_pwm = cfg->htim_pwm;
    servo->channel_number = cfg->channel_number;

    servo->ccr_min =
        (uint16_t)(cfg->pulse_min *
                   (float)__HAL_TIM_GET_AUTORELOAD(servo->htim_pwm) / 0.02f);
    servo->ccr_max =
        (uint16_t)(cfg->pulse_max *
                   (float)__HAL_TIM_GET_AUTORELOAD(servo->htim_pwm) / 0.02f);

    servo->angle_max = cfg->angle_max;

    set_servo_angle(servo, 0.0f);

    if (cfg->interrupt_mode == 1)
        HAL_TIM_PWM_Start_IT(cfg->htim_pwm, cfg->channel_number);
    else
        HAL_TIM_PWM_Start(cfg->htim_pwm, cfg->channel_number);
}

int set_servo_angle(ServoMotor* servo, float angle) {
    if (angle > servo->angle_max) return -1;
    if (angle < 0) return -1;

    __HAL_TIM_SET_COMPARE(
        servo->htim_pwm, servo->channel_number,
        servo->ccr_min +
            (uint16_t)(angle * (float)(servo->ccr_max - servo->ccr_min) /
                       servo->angle_max));

    return 0;
}

float get_servo_angle(ServoMotor* servo) {
    return (float)(__HAL_TIM_GET_COMPARE(servo->htim_pwm,
                                         servo->channel_number) -
                   servo->ccr_min) /
           (float)(servo->ccr_max - servo->ccr_min) * servo->angle_max;
}