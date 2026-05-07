#ifndef DRIVERS_CUSTOM_SERVO_H
#define DRIVERS_CUSTOM_SERVO_H

#include "stm32l4xx_hal.h"

typedef struct {
    TIM_HandleTypeDef *htim;
    uint32_t channel;
    float min_pulse_ms;
    float max_pulse_ms;
} ServoConfig;

void SERVO_Init(ServoConfig *config);
void SERVO_SetAngle(ServoConfig *config, float angle);

#endif