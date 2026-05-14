//
// Created by maxim on 12/05/2026.
//

#include "flip_task.h"

static CommandeColors couleur_terrain = {0, 0, 0, 0, 0};
static osMutexId_t couleur_terrain_mutex;

void StartFlipTask(void *argument) {
    FlipTaskParams* params = (FlipTaskParams*)(argument);

    set_servo_angle(&params->servo_return_1, 10.0f);
    set_servo_angle(&params->servo_return_2, 10.0f);
    set_servo_angle(&params->servo_return_3, 10.0f);
    set_servo_angle(&params->servo_return_4, 10.0f);

    osDelay(500);

    set_servo_angle(&params->servo_return_1, 90.0f);
    set_servo_angle(&params->servo_return_2, 90.0f);
    set_servo_angle(&params->servo_return_3, 90.0f);
    set_servo_angle(&params->servo_return_4, 90.0f);

    osDelay(500);

    set_servo_angle(&params->servo_return_1, 10.0f);
    set_servo_angle(&params->servo_return_2, 10.0f);
    set_servo_angle(&params->servo_return_3, 10.0f);
    set_servo_angle(&params->servo_return_4, 10.0f);

    CommandeColors couleur_recup = {};

    while (1) {
        osThreadFlagsWait(FLIP_TASK_START_FLAG, 0, osWaitForever);

        if (osMutexAcquire(couleur_terrain_mutex, 2) == osOK) {
            couleur_recup = couleur_terrain;
            osMutexRelease(couleur_terrain_mutex);
        }

        if (couleur_recup.color_team == couleur_recup.color_brick_1) {
            if (get_servo_angle(&params->servo_return_1) > 90) {
                set_servo_angle(&params->servo_return_1, 10.0f);
            }
            if (get_servo_angle(&params->servo_return_1) < 90) {
                set_servo_angle(&params->servo_return_1, 180.0f);
            }
        }
        if (couleur_recup.color_team == couleur_recup.color_brick_2) {
            if (get_servo_angle(&params->servo_return_2) > 90) {
                set_servo_angle(&params->servo_return_2, 10.0f);
            }
            if (get_servo_angle(&params->servo_return_2) < 90) {
                set_servo_angle(&params->servo_return_2, 180.0f);
            }
        }
        if (couleur_recup.color_team == couleur_recup.color_brick_3) {
            if (get_servo_angle(&params->servo_return_3) > 90) {
                set_servo_angle(&params->servo_return_3, 10.0f);
            }
            if (get_servo_angle(&params->servo_return_3) < 90) {
                set_servo_angle(&params->servo_return_3, 180.0f);
            }
        }
        if (couleur_recup.color_team == couleur_recup.color_brick_4) {
            if (get_servo_angle(&params->servo_return_4) > 90) {
                set_servo_angle(&params->servo_return_4, 10.0f);
            }
            if (get_servo_angle(&params->servo_return_4) < 90) {
                set_servo_angle(&params->servo_return_4, 180.0f);
            }
        }

        osThreadFlagsSet(*params->strategy_task, STRAT_BIT_FLIP);
    }
}