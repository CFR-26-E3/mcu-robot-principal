//
// Created by maxim on 13/05/2026.
//

#include "ultrason.h"

#include "../../App_Logic/Inc/robot_config.h"

void init_ultrasensor(CapteurUS* capteur, const CapteurUSConfig* config) {
    capteur->htim = config->htim;
    capteur->channel_number = config->channel_number;
    capteur->port_trigger = config->port_trigger;
    capteur->pin_trigger = config->pin_trigger;
    capteur->port_echo = config->port_echo;
    capteur->pin_echo = config->pin_echo;
    capteur->distance = 0.0f;

    HAL_TIM_IC_Start_IT(capteur->htim, capteur->channel_number);
}

void ultrason_isr(CapteurUS *capteur, TIM_HandleTypeDef *htim) {
    if (htim == capteur->htim) {
        if (HAL_GPIO_ReadPin(capteur->port_echo, capteur->pin_echo) == GPIO_PIN_SET) {
            capteur->prev_cnt = __HAL_TIM_GetCompare(capteur->htim, capteur->channel_number);
        } else {
            uint32_t cnt = __HAL_TIM_GetCompare(capteur->htim, capteur->channel_number);
            if (cnt >= capteur->prev_cnt) {
                capteur->distance = (float)(cnt - capteur->prev_cnt) * DETECTION_TIMER_PERIOD * SOUND_SPEED / 2.0f;
            } else {
                capteur->distance = (float)(__HAL_TIM_GetAutoreload(capteur->htim) + cnt - capteur->prev_cnt + 1) * DETECTION_TIMER_PERIOD * SOUND_SPEED / 2.0f;
            }
        }
    }
}

void start_ultrasensor_measure(CapteurUS *capteur) {
    HAL_GPIO_WritePin(capteur->port_trigger, capteur->pin_trigger, GPIO_PIN_SET);
    for (volatile uint32_t i = 0; i < 300; i++) {
        __NOP();
    }
    HAL_GPIO_WritePin(capteur->port_trigger, capteur->pin_trigger, GPIO_PIN_RESET);
}