//
// Created by maxim on 13/05/2026.
//
#include "Detection_task.h"

// timer

static int detection_active_capteurUS_Av_Ga;
static osMutexId_t detection_active_capteurUS_Av_Ga_mutex;

static int detection_active_capteurUS_Av_Dr;
static osMutexId_t detection_active_capteurUS_Av_Dr_mutex;

static int detection_active_capteurUS_Ar_Ga;
static osMutexId_t detection_active_capteurUS_Ar_Ga_mutex;

void StartDetectionTask(void* argument) {
    DetectionTaskParams* params = (DetectionTaskParams*)(argument);
    int detection_active = 0;
    CapteurUS capteurs[3] = {params->CapteurUltrason_AV_GA,
                             params->CapteurUltrason_AV_DR,
                             params->CapteurUltrason_AR_GA};
    while (1) {
        for (int i = 0; i < 3; i++) {
            // on lit la distance (mm)
            detection_active = 0;
            uint32_t distance = Get_distance(&capteurs[i]);

            // est-ce qu'il y a un obstacle
            if (distance > 20 && distance < DISTANCE_SECURITE_DEFAUT) {
                detection_active = 1;
            }
            if (i == 0) {
                if (osMutexAcquire(detection_active_capteurUS_Av_Ga_mutex, 2) ==
                    osOK) {
                    detection_active_capteurUS_Av_Ga = detection_active;
                    osMutexRelease(detection_active_capteurUS_Av_Ga_mutex);
                }
            }
            if (i == 1) {
                if (osMutexAcquire(detection_active_capteurUS_Av_Dr_mutex, 2) ==
                    osOK) {
                    detection_active_capteurUS_Av_Dr = detection_active;
                    osMutexRelease(detection_active_capteurUS_Av_Dr_mutex);
                }
            }
            if (i == 2) {
                if (osMutexAcquire(detection_active_capteurUS_Ar_Ga_mutex, 2) ==
                    osOK) {
                    detection_active_capteurUS_Ar_Ga = detection_active;
                    osMutexRelease(detection_active_capteurUS_Ar_Ga_mutex);
                }
            }
            // delai pour éviter les interférences entre les capteurs
            osDelay(DETECTION_TASK_PERIODE_INTERFERENCE);
        }

        // pause
        osDelay(DETECTION_TASK_PERIODE);
    }
}

int Get_obstacle_av_ga() {
    int i = 0;
    if (osMutexAcquire(detection_active_capteurUS_Av_Ga_mutex, 2) == osOK) {
        i = detection_active_capteurUS_Av_Ga;
        osMutexRelease(detection_active_capteurUS_Av_Ga_mutex);
    }
    return i;
}

int Get_obstacle_av_dr() {
    int i = 0;
    if (osMutexAcquire(detection_active_capteurUS_Av_Dr_mutex, 2) == osOK) {
        i = detection_active_capteurUS_Av_Dr;
        osMutexRelease(detection_active_capteurUS_Av_Dr_mutex);
    }
    return i;
}

int Get_obstacle_ar_ga() {
    int i = 0;
    if (osMutexAcquire(detection_active_capteurUS_Ar_Ga_mutex, 2) == osOK) {
        i = detection_active_capteurUS_Ar_Ga;
        osMutexRelease(detection_active_capteurUS_Ar_Ga_mutex);
    }
    return i;
}