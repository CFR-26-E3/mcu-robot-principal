#ifndef MCU_ROBOT_PRINCIPAL_DC_MOTOR_H
#define MCU_ROBOT_PRINCIPAL_DC_MOTOR_H

#include "stm32l4xx_hal.h"

typedef struct {
    TIM_HandleTypeDef *htim_pwm;
    int channel_number;
    uint32_t arr_reg_val;

    GPIO_TypeDef *dir_port_a;
    uint32_t dir_pin_a;
    GPIO_TypeDef *dir_port_b;
    uint32_t dir_pin_b;

    float power_scale;
} DcMotor;

/**
 * Configuration struct for initializing a DC motor. This struct contains all
 * necessary information to set up the motor, including the PWM timer and
 * channel, as well as the GPIO ports and pins used for controlling the motor
 * direction.
 */
typedef struct {
    TIM_HandleTypeDef *htim_pwm;  // PWM Timer handle
    int channel_number;           // Timer channel number (e.g., TIM_CHANNEL_1)
    GPIO_TypeDef *dir_port_a;     // GPIO port for direction pin A
    uint16_t dir_pin_a;           // GPIO pin number for direction pin A
    GPIO_TypeDef *dir_port_b;     // GPIO port for direction pin B
    uint16_t dir_pin_b;           // GPIO pin number for direction pin B
    float power_scale;  // Scale factor to convert PWM value to actual motor
                        // voltage (0.0 to 1.0)
} DcMotorConfig;

/**
 * @brief Initializes a DC motor with the specified configuration.
 *
 * This function starts the PWM timer and direction control pins for the DC
 * motor based on the provided configuration. It also calculates the ARR
 * register value for the PWM timer to ensure that the PWM signal is generated
 * at the correct frequency.
 *
 * @param motor Pointer to a DcMotor structure that will be initialized.
 * @param cfg Pointer to a DcMotorConfig structure containing the configuration
 *            parameters for the motor.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int init_dc_motor(DcMotor *motor, const DcMotorConfig *cfg);

/**
 * @brief Sets the PWM value for a DC motor.
 *
 * This function updates the PWM duty cycle for the specified DC motor based on
 * the provided PWM value. The PWM value should be in the range of -1.0 to 1.0,
 * where positive values indicate forward direction and negative values indicate
 * reverse direction. The function also updates the direction control pins
 * accordingly.
 *
 * @param motor Pointer to a DcMotor structure representing the motor to be
 *              controlled.
 * @param pwm_val A float value representing the desired PWM duty cycle, where
 *                -1.0 <= pwm_val <= 1.0.
 * @return int Returns 0 on success, or a negative error code on failure.
 */
int set_dc_motor_pwm(const DcMotor *motor, float pwm_val);

#endif  // MCU_ROBOT_PRINCIPAL_DC_MOTOR_H
