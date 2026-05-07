#include "servo.h"

void SERVO_Init(ServoConfig *config) {
    HAL_TIM_PWM_Start(config->htim, config->channel);
}

void SERVO_SetAngle(ServoConfig *config, float angle) {
    if (angle < 0.0f) angle = 0.0f;
    if (angle > 180.0f) angle = 180.0f;

    uint32_t arr = config->htim->Instance->ARR;
    
    // Calcul de la largeur d'impulsion (0.5ms à 2.5ms pour MG996R)
    float pulse_ms = config->min_pulse_ms + (angle / 180.0f) * (config->max_pulse_ms - config->min_pulse_ms);
    
    // Conversion en valeur CCR : (pulse_ms / période_20ms) * (ARR + 1)
    uint32_t ccr_value = (uint32_t)((pulse_ms / 20.0f) * (arr + 1));
    
    __HAL_TIM_SET_COMPARE(config->htim, config->channel, ccr_value);
}