#ifndef MCU_ROBOT_PRINCIPAL_SEND_SPEED_H
#define MCU_ROBOT_PRINCIPAL_SEND_SPEED_H

#include <stdio.h>
#include <string.h>

#include "cmsis_os2.h"
#include "encoder.h"
#include "pid_controller.h"
#include "robot_config.h"

typedef struct {
    Encoder left_encoder;
    Encoder right_encoder;
    UART_HandleTypeDef *huart;
} SendSpeedTaskParam;

void StartSendSpeedTask(void *argument);

#endif  // MCU_ROBOT_PRINCIPAL_SEND_SPEED_H
