//
// Created by maxim on 13/05/2026.
//

#ifndef MCU_ROBOT_PRINCIPAL_ULTRASON_H
#define MCU_ROBOT_PRINCIPAL_ULTRASON_H
#include "stm32f7xx_hal.h"

typedef struct {
    TIM_HandleTypeDef* htim;
    int channel_number;
    GPIO_TypeDef* port_trigger;
    uint16_t pin_trigger;
    GPIO_TypeDef* port_echo;
    uint16_t pin_echo;
} CapteurUSConfig;

typedef struct {
    TIM_HandleTypeDef* htim;
    int channel_number;
    GPIO_TypeDef* port_trigger;
    uint16_t pin_trigger;
    GPIO_TypeDef* port_echo;
    uint16_t pin_echo;

    uint32_t prev_cnt;
    uint8_t is_measuring;
    float distance;
} CapteurUS;

void init_ultrasensor(CapteurUS* capteur, const CapteurUSConfig* config);

void ultrason_isr(CapteurUS *capteur, TIM_HandleTypeDef *htim);

void start_ultrasensor_measure(CapteurUS *capteur);

#endif  // MCU_ROBOT_PRINCIPAL_ULTRASON_H
