#include "stepper_motor.h"

#include <stdio.h>

int init_stepper_motor(StepperMotor *motor, const StepperMotorConfig *cfg) {
    motor->htim_step = cfg->htim_step;
    motor->dir_port = cfg->dir_port;
    motor->dir_pin = cfg->dir_pin;
    motor->step_active = 0;

    motor->step_port = cfg->step_port;
    motor->step_pin = cfg->step_pin;

    motor->current_steps = 0;
    motor->target_steps = 0;

    motor->accel_steps =
        (uint32_t)(((uint64_t)cfg->motor_max_speed * cfg->motor_max_speed -
                    (uint64_t)cfg->motor_min_speed * cfg->motor_min_speed) /
                   (2 * cfg->motor_accel));  // Steps needed to accelerate from
                                             // min to max speed
    motor->sequence_steps = 0;

    motor->dds_min_speed =
        (uint32_t)(((uint64_t)cfg->motor_min_speed << 32) /
                   cfg->tim_freq_hz);  // Convert min speed to DDS increment
    motor->dds_max_speed =
        (uint32_t)(((uint64_t)cfg->motor_max_speed << 32) / cfg->tim_freq_hz);
    motor->dds_accel_increment =
        (uint32_t)(((uint64_t)cfg->motor_accel << 32) /
                   ((uint64_t)cfg->tim_freq_hz * cfg->tim_freq_hz));
    motor->dds_accumulator = 0;
    motor->dds_speed = 0;

    if (!(motor->htim_step->Instance->CR1 & TIM_CR1_CEN))
        HAL_TIM_Base_Start_IT(motor->htim_step);

    return 0;
}

int turn_stepper_motor_to_target_steps(StepperMotor *motor,
                                       int32_t target_steps) {
    motor->target_steps = target_steps;

    if (motor->target_steps > motor->current_steps) {
        HAL_GPIO_WritePin(motor->dir_port, motor->dir_pin, GPIO_PIN_SET);
    } else if (motor->target_steps < motor->current_steps) {
        HAL_GPIO_WritePin(motor->dir_port, motor->dir_pin, GPIO_PIN_RESET);
    } else {
        // Already at target position
        return 0;
    }

    motor->sequence_steps = 0;

    return 0;
}

void stepper_motor_int_handle(StepperMotor *motor) {
    if (motor->step_active) {
        HAL_GPIO_WritePin(motor->step_port, motor->step_pin, GPIO_PIN_RESET);
        motor->step_active = 0;
    }

    if (motor->current_steps == motor->target_steps) {
        motor->dds_speed = 0;
        return;
    }

    // DDS Accumulator Update
    uint32_t prev_acc = motor->dds_accumulator;
    motor->dds_accumulator += motor->dds_speed;

    // If the accumulator overflows (wraps around), it means it's time to
    // generate a step pulse
    if (motor->dds_accumulator < prev_acc) {
        HAL_GPIO_WritePin(motor->step_port, motor->step_pin, GPIO_PIN_SET);
        motor->step_active = 1;

        if (motor->target_steps > motor->current_steps) {
            motor->current_steps++;
        } else {
            motor->current_steps--;
        }
        motor->sequence_steps++;
    }

    // Ramp generation logic for acceleration and deceleration
    // Get the absolute number of steps remaining to the target
    uint32_t remaining_steps =
        (motor->target_steps > motor->current_steps)
            ? (motor->target_steps - motor->current_steps)
            : (motor->current_steps - motor->target_steps);

    // If the number of steps is less than the number of steps needed to
    // accelerate, the speed profile could be triangular instead of trapezoidal.
    // In that case, the braking should start now to ensure we can
    // decelerate to stop at the target position.
    uint32_t brake_limit = (motor->sequence_steps < motor->accel_steps)
                               ? motor->sequence_steps
                               : motor->accel_steps;

    if (remaining_steps <= brake_limit) {
        // This ensures we can decrement the speed without risking a wrapping.
        if (motor->dds_speed >
            motor->dds_min_speed + motor->dds_accel_increment) {
            motor->dds_speed -= motor->dds_accel_increment;
        } else {
            motor->dds_speed = motor->dds_min_speed;
        }
    } else if (motor->dds_speed < motor->dds_max_speed) {
        motor->dds_speed += motor->dds_accel_increment;
    }
}

int stop_stepper_motor(StepperMotor *motor) {
    motor->dds_speed = 0;
    motor->target_steps = motor->current_steps;

    return 0;
}

int reset_steps_stepper_motor(StepperMotor *motor) {
    motor->current_steps = 0;
    return 0;
}

int32_t get_stepper_motor_current_steps(StepperMotor *motor) {
    return motor->current_steps;
}
