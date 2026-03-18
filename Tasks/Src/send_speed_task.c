#include "send_speed_task.h"

static float compute_wheel_speed(uint32_t prev_ticks, uint32_t ticks) {
    int32_t diff_left = (int32_t)prev_ticks - (int32_t)ticks;

    if (diff_left > (TICKS_PER_REV_WHEELS / 2))
        diff_left -= TICKS_PER_REV_WHEELS;
    else if (diff_left < -(TICKS_PER_REV_WHEELS / 2))
        diff_left += TICKS_PER_REV_WHEELS;

    return (float)(diff_left) / ((float)ODOMETRY_PERIOD * 0.001f) /
           (float)TICKS_PER_REV_WHEELS * 60.0f;
}

void StartSendSpeedTask(void *argument) {
    SendSpeedTaskParam *params = (SendSpeedTaskParam *)argument;
    uint32_t ticks = osKernelGetTickCount();

    uint32_t prev_left_ticks = 0;
    uint32_t prev_right_ticks = 0;

    while (1) {
        float left_speed = compute_wheel_speed(
            prev_left_ticks, get_encoder_ticks(&params->left_encoder));
        prev_left_ticks = get_encoder_ticks(&params->left_encoder);
        float right_speed = compute_wheel_speed(
            prev_right_ticks, get_encoder_ticks(&params->right_encoder));
        prev_right_ticks = get_encoder_ticks(&params->right_encoder);

        char buffer[30];
        size_t len =
            snprintf(buffer, sizeof(buffer), "%f;%f", left_speed, right_speed);

        HAL_UART_Transmit(params->huart, buffer, len, 10);
        HAL_UART_Transmit(params->huart, "\n\r", 2, 10);

        ticks += ODOMETRY_PERIOD;
        osDelayUntil(ticks);
    }
}
