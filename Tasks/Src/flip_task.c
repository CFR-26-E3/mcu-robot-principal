//
// Created by maxim on 12/05/2026.
//

#include "flip_task.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim8;

extern osThreadId_t Strat_taskHandle;

static CommandeColors couleur_terrain = {0, 0, 0, 0, 0};
static osMutexId_t couleur_terrain_mutex;

void StartReturnTask(void *argument) {
    set_servo_angle(&ServoReturn1, 10.0f);
    set_servo_angle(&ServoReturn2, 10.0f);
    set_servo_angle(&ServoReturn3, 10.0f);
    set_servo_angle(&ServoReturn4, 10.0f);
    CommandeColors couleur_recup;
    while (1) {
        osThreadFlagsWait(1, 0, osWaitForever);
        if (osMutexAcquire(couleur_terrain_mutex, 2) == osOK) {
            couleur_recup = couleur_terrain;
            osMutexRelease(couleur_terrain_mutex);
        }

        if (couleur_recup[0] = couleur_recup[1]) {
            if (get_servo_angle(&ServoReturn1) > 90) {
                set_servo_angle(&ServoReturn1, 10.0f);
            }
            if (get_servo_angle(&ServoReturn1) < 90) {
                set_servo_angle(&ServoReturn1, 180.0f);
            }
        }
        if (couleur_recup[0] = couleur_recup[2]) {
            if (get_servo_angle(&ServoReturn2) > 90) {
                set_servo_angle(&ServoReturn2, 10.0f);
            }
            if (get_servo_angle(&ServoReturn2) < 90) {
                set_servo_angle(&ServoReturn2, 180.0f);
            }
        }
        if (couleur_recup[0] = couleur_recup[3]) {
            if (get_servo_angle(&ServoReturn3) > 90) {
                set_servo_angle(&ServoReturn3, 10.0f);
            }
            if (get_servo_angle(&ServoReturn3) < 90) {
                set_servo_angle(&ServoReturn3, 180.0f);
            }
        }
        if (couleur_recup[0] = couleur_recup[4]) {
            if (get_servo_angle(&ServoReturn4) > 90) {
                set_servo_angle(&ServoReturn4, 10.0f);
            }
            if (get_servo_angle(&ServoReturn4) < 90) {
                set_servo_angle(&ServoReturn4, 180.0f);
            }
        }
        // osThreadFlagsSet(*argument->, 1);
    }
}