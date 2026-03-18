#include "dc_motor.h"

int init_dc_motor(DcMotor *motor, const DcMotorConfig *cfg) {
    motor->htim_pwm = cfg->htim_pwm;
    motor->channel_number = cfg->channel_number;
    motor->arr_reg_val = __HAL_TIM_GET_AUTORELOAD(motor->htim_pwm);

    motor->dir_port_a = cfg->dir_port_a;
    motor->dir_pin_a = cfg->dir_pin_a;
    motor->dir_port_b = cfg->dir_port_b;
    motor->dir_pin_b = cfg->dir_pin_b;

    motor->power_scale = cfg->power_scale;

    HAL_TIM_PWM_Start(cfg->htim_pwm, cfg->channel_number);

    return 0;
}

int set_dc_motor_pwm(const DcMotor *motor, float pwm_val) {
    if (pwm_val > 1.0f) pwm_val = 1.0f;
    if (pwm_val < -1.0f) pwm_val = -1.0f;

    if (pwm_val > 0.0f) {
        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_number,
                              (uint32_t)((float)motor->arr_reg_val * pwm_val *
                                         motor->power_scale));

        HAL_GPIO_WritePin(motor->dir_port_a, motor->dir_pin_a, GPIO_PIN_SET);
        HAL_GPIO_WritePin(motor->dir_port_b, motor->dir_pin_b, GPIO_PIN_RESET);
    } else if (pwm_val == 0.0f) {
        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_number, 0);

        HAL_GPIO_WritePin(motor->dir_port_a, motor->dir_pin_a, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor->dir_port_b, motor->dir_pin_b, GPIO_PIN_RESET);
    } else {
        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_number,
                              (uint32_t)((float)motor->arr_reg_val * -pwm_val *
                                         motor->power_scale));

        HAL_GPIO_WritePin(motor->dir_port_a, motor->dir_pin_a, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(motor->dir_port_b, motor->dir_pin_b, GPIO_PIN_SET);
    }

    return 0;
}