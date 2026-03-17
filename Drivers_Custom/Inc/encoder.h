#ifndef MCU_ROBOT_PRINCIPAL_ENCODER_H
#define MCU_ROBOT_PRINCIPAL_ENCODER_H

#include "stm32l4xx_hal.h"

typedef struct {
    TIM_HandleTypeDef *htim;
} EncoderConfig;

typedef struct {
    TIM_HandleTypeDef *htim;
} Encoder;

int init_encoder(Encoder *encoder, EncoderConfig *cfg);

uint32_t get_encoder_ticks(Encoder *encoder);

#endif  // MCU_ROBOT_PRINCIPAL_ENCODER_H
