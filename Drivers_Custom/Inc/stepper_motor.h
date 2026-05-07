#ifndef MCU_ROBOT_PRINCIPAL_STEPPER_MOTOR_H
#define MCU_ROBOT_PRINCIPAL_STEPPER_MOTOR_H

#include "stm32f7xx_hal.h"

typedef struct {
    TIM_HandleTypeDef
        *htim_step;        // Timer handle for generating step pulses with DDS
    uint32_t tim_freq_hz;  // Timer frequency in Hz (after prescaling)

    GPIO_TypeDef *step_port;
    uint16_t step_pin;

    GPIO_TypeDef *dir_port;
    uint16_t dir_pin;

    uint16_t motor_min_speed;  // Min speed in steps/s
    uint16_t motor_max_speed;  // Max speed in steps/s
    uint16_t motor_accel;      // Acceleration in steps/s^2
} StepperMotorConfig;

typedef struct {
    TIM_HandleTypeDef *htim_step;
    uint32_t tim_freq_hz;  // Timer frequency in Hz (after prescaling)

    uint8_t step_active;  // Flag to indicate if a step pulse is currently
                          // active (high)
    GPIO_TypeDef *step_port;
    uint16_t step_pin;

    GPIO_TypeDef *dir_port;
    uint16_t dir_pin;

    int32_t current_steps;
    int32_t target_steps;

    uint32_t
        accel_steps;  // Number of steps to accelerate from min to max speed
    uint32_t sequence_steps;  // Number of steps in the current moving sequence
                              // (used for acceleration/deceleration)

    uint32_t dds_min_speed;        // Min increment for DDS speed control
                                   // (corresponding to motor_min_speed)
    uint32_t dds_max_speed;        // Max increment for DDS speed control
                                   // (corresponding to motor_max_speed)
    uint32_t dds_accel_increment;  // Precomputed increment for DDS acceleration
    uint32_t dds_speed;  // Current DDS increment value for speed control
    uint32_t
        dds_accumulator;  // Current DDS accumulator value for speed control

    uint8_t
        is_resetting;  // The motor is currently finding its starting position
    uint32_t dds_max_resetting_speed;
} StepperMotor;

/** @brief Initializes a stepper motor with the specified configuration.
 *
 * This function sets up the stepper motor by configuring the timer for
 * generating step pulses and the GPIO pin for controlling the motor direction.
 *
 * @remark The prescaled timer clock is assumed to be 50 kHz.
 *
 * @param motor The StepperMotor structure to be initialized.
 * @param cfg The configuration parameters for the stepper motor.
 * @return 0 on success.
 */
int init_stepper_motor(StepperMotor *motor, const StepperMotorConfig *cfg);

/** @brief Turns the stepper motor to a target position specified in steps.
 *
 * This function sets the target position for the stepper motor and updates the
 * direction pin accordingly. The actual movement towards the target position
 * will be handled in the timer interrupt handler, which will generate step
 * pulses based on the current speed and acceleration profile.
 *
 * @param motor The StepperMotor structure representing the motor to be
 * controlled.
 * @param target_steps The desired target position in steps (can be positive or
 *                     negative).
 * @return 0 on success.
 */
int turn_stepper_motor_to_target_steps(StepperMotor *motor,
                                       int32_t target_steps);

/** @brief Timer interrupt handler for the stepper motor.
 *
 * This function should be called from the timer interrupt service routine. It
 * handles the generation of step pulses based on the current speed and
 * acceleration profile, and updates the current position of the motor. It also
 * manages the ramping up and down of the motor speed to ensure smooth movement
 * towards the target position.
 *
 * @param motor The StepperMotor structure representing the motor being
 * controlled.
 */
void stepper_motor_int_handle(StepperMotor *motor);

/** @brief Stops the stepper motor.
 *
 * @param motor The StepperMotor structure representing the motor to be stopped.
 * @return 0 on success.
 */
int stop_stepper_motor(StepperMotor *motor);

/** @brief Gets the current position of the stepper motor in steps.
 *
 * @param motor The StepperMotor structure representing the motor being
 * controlled.
 * @return The current position of the motor in steps.
 */
int32_t get_stepper_motor_current_steps(StepperMotor *motor);

/** @brief Resets the position of the motor to 0;
 *
 * @param motor The StepperMotor structure representing the motor being
 * controlled.
 * @return The current position of the motor in steps.
 */
int reset_steps_stepper_motor(StepperMotor *motor);

int reset_stepper_motor(StepperMotor *motor);

#endif  // MCU_ROBOT_PRINCIPAL_STEPPER_MOTOR_H
