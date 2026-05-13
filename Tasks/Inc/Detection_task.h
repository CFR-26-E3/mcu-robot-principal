//
// Created by maxim on 13/05/2026.
//

#ifndef MCU_ROBOT_PRINCIPAL_DETECTION_TASK_H
#define MCU_ROBOT_PRINCIPAL_DETECTION_TASK_H
#include "cmsis_os.h"
#include "robot_config.h"
#include "ultrason.h"
typedef struct {
    CapteurUS CapteurUltrason_AV_DR;
    CapteurUS CapteurUltrason_AV_GA;
    CapteurUS CapteurUltrason_AR_GA;
    osThreadId_t *strategy_task;
} DetectionTaskParams;
void StartDetectionTask(void *argument);
int Get_obstacle_av_ga();
int Get_obstacle_av_dr();
int Get_obstacle_ar_ga();
#endif  // MCU_ROBOT_PRINCIPAL_DETECTION_TASK_H
