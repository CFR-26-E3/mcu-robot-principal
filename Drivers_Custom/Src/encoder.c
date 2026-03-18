#include "encoder.h"

int init_encoder(Encoder *encoder, EncoderConfig *cfg) {
    encoder->htim = cfg->htim;

    HAL_TIM_Encoder_Start(encoder->htim, TIM_CHANNEL_ALL);

    return 0;
}

uint32_t get_encoder_ticks(Encoder *encoder) {
    return __HAL_TIM_GET_COUNTER(encoder->htim);
}