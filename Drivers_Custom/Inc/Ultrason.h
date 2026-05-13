//
// Created by maxim on 13/05/2026.
//

#ifndef MCU_ROBOT_PRINCIPAL_ULTRASON_H
#define MCU_ROBOT_PRINCIPAL_ULTRASON_H
#include "stm32f7xx_hal.h"

typedef struct {
    TIM_HandleTypeDef* htim_pwm;
    GPIO_TypeDef* port_trigger;
    uint16_t pin_trigger;
    GPIO_TypeDef* port_echo;
    uint16_t pin_echo;
    uint32_t distance_mm;
} CapteurUSConfig;

typedef struct {
    TIM_HandleTypeDef* htim_pwm;
    GPIO_TypeDef* port_trigger;
    uint16_t pin_trigger;
    GPIO_TypeDef* port_echo;
    uint16_t pin_echo;
    uint32_t distance_mm;
} CapteurUS;
void init_ultrasensor(CapteurUS* capteur, const CapteurUSConfig* config);
uint32_t Get_distance(CapteurUS* capteur);
#endif  // MCU_ROBOT_PRINCIPAL_ULTRASON_H
