//
// Created by maxim on 13/05/2026.
//

#include "Ultrason.h"

void init_ultrasensor(CapteurUS* capteur, const CapteurUSConfig* capteurUS) {
    capteur->htim_pwm = capteurUS->htim_pwm;
    capteur->port_trigger = capteurUS->port_trigger;
    capteur->pin_trigger = capteurUS->pin_trigger;
    capteur->port_echo = capteurUS->port_echo;
    capteur->pin_echo = capteurUS->pin_echo;
    capteur->distance_mm = 0;
}

uint32_t Get_distance(CapteurUS* capteur) {
    uint32_t temps_echo_us = 0;

    // signal trigger -> 10 mircos
    HAL_GPIO_WritePin(capteur->port_trigger, capteur->pin_trigger,
                      GPIO_PIN_SET);
    __HAL_TIM_SET_COUNTER(capteur->htim_pwm, 0);
    while (__HAL_TIM_GET_COUNTER(capteur->htim_pwm) < 10) {
        HAL_GPIO_WritePin(capteur->port_trigger, capteur->pin_trigger,
                          GPIO_PIN_RESET);

        // on attend le retour de echo
        uint32_t timeout = 10000;
        while (HAL_GPIO_ReadPin(capteur->port_echo, capteur->pin_echo) ==
                   GPIO_PIN_RESET &&
               timeout > 0) {
            timeout--;
        }

        // on mesure la durée de echo
        __HAL_TIM_SET_COUNTER(capteur->htim_pwm,
                              0);  // on remet à zéro dès que echo passe à haut
        while (HAL_GPIO_ReadPin(capteur->port_echo, capteur->pin_echo) ==
               GPIO_PIN_SET) {
            temps_echo_us = __HAL_TIM_GET_COUNTER(capteur->htim_pwm);
            if (temps_echo_us > 30000)
                break;  // on sort s'il n'y a pas d'obstacles
        }

        // calcul de la distance
        capteur->distance_mm = (uint32_t)(temps_echo_us * 0.17);

        return capteur->distance_mm;
    }
}