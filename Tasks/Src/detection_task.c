//
// Created by maxim on 13/05/2026.
//
#include "detection_task.h"

// timer

static float distance_capteurUS_Av_Ga = 0.0f;
static osMutexId_t distance_capteurUS_Av_Ga_mutex;

static float distance_capteurUS_Av_Dr = 0.0f;
static osMutexId_t distance_capteurUS_Av_Dr_mutex;

DetectionTaskParams* params;

void StartDetectionTask(void* argument) {
    params = (DetectionTaskParams*)(argument);

    distance_capteurUS_Av_Dr_mutex = osMutexNew(NULL);
    distance_capteurUS_Av_Ga_mutex = osMutexNew(NULL);

    CapteurUS capteurs[] = {params->CapteurUltrason_AV_GA, params->CapteurUltrason_AV_DR};

    while (1) {
        for (int i = 0; i < 2; i++) {
            start_ultrasensor_measure(&capteurs[i]);
            osDelay(DETECTION_TASK_PERIODE_INTERFERENCE);
        }

        // pause
        osDelay(DETECTION_TASK_PERIODE);
    }
}

float GetDistanceCapteurUSAvGa() {
    if (osMutexAcquire(distance_capteurUS_Av_Ga_mutex, 5) == osOK) {
        float distance_capteurUS_Av_Ga_safe = params->CapteurUltrason_AV_GA.distance;
        osMutexRelease(distance_capteurUS_Av_Ga_mutex);
        return distance_capteurUS_Av_Ga_safe;
    }

    return 0.0f;
}

float GetDistanceCapteurUSAvDr() {
    if (osMutexAcquire(distance_capteurUS_Av_Dr_mutex, 5) == osOK) {
        float distance_capteurUS_Av_Dr_safe = params->CapteurUltrason_AV_DR.distance;
        osMutexRelease(distance_capteurUS_Av_Dr_mutex);
        return distance_capteurUS_Av_Dr_safe;
    }

    return 0.0f;
}