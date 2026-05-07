#ifndef MCU_ROBOT_PRINCIPAL_SERVO_MOTOR_H
#define MCU_ROBOT_PRINCIPAL_SERVO_MOTOR_H
#include "stm32f7xx_hal.h"

typedef struct {
    TIM_HandleTypeDef* htim_pwm;
    int channel_number;

    float pulse_min;  // minimal pulse width in s
    float pulse_max;

    float angle_max;  // angle range of the servo (0 to ...)

    uint8_t interrupt_mode;  // if 1, the timer will generate interrupts
} ServoMotorConfig;

typedef struct {
    TIM_HandleTypeDef* htim_pwm;
    int channel_number;

    uint16_t ccr_min;
    uint16_t ccr_max;

    float angle_max;
} ServoMotor;

void init_servo_motor(ServoMotor* servo, ServoMotorConfig* cfg);

int set_servo_angle(ServoMotor* servo, float angle);

float get_servo_angle(ServoMotor* servo);

#endif  // MCU_ROBOT_PRINCIPAL_SERVO_MOTOR_H
