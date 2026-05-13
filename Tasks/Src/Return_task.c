//
// Created by maxim on 12/05/2026.
//

#include "Return_task.h"

#include "Strat_task.h"
#include "main.h"
#include "servo_motor.h"

extern ServoMotor ServoReturn1;
extern ServoMotor ServoReturn2;
extern ServoMotor ServoReturn3;
extern ServoMotor ServoReturn4;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim8;

extern osThreadId_t Strat_taskHandle;

static CommandeColors couleur_terrain = {0, 0, 0, 0, 0};
static osMutexId_t couleur_terrain_mutex;

void StartReturnTask(void *argument) {
    ServoMotorConfig Return_1_Cfg = {.htim_pwm = &htim8,
                                     .channel_number = TIM_CHANNEL_2,
                                     .pulse_min = 0.0005f,  // 0.5ms en secondes
                                     .pulse_max = 0.0025f,  // 2.5ms en secondes
                                     .angle_max = 180.0f,
                                     .interrupt_mode = 0};

    ServoMotorConfig Return_2_Cfg = {.htim_pwm = &htim8,
                                     .channel_number = TIM_CHANNEL_3,
                                     .pulse_min = 0.0005f,  // 0.5ms en secondes
                                     .pulse_max = 0.0025f,  // 2.5ms en secondes
                                     .angle_max = 180.0f,
                                     .interrupt_mode = 0};

    ServoMotorConfig Return_3_Cfg = {.htim_pwm = &htim8,
                                     .channel_number = TIM_CHANNEL_4,
                                     .pulse_min = 0.0005f,  // 0.5ms en secondes
                                     .pulse_max = 0.0025f,  // 2.5ms en secondes
                                     .angle_max = 180.0f,
                                     .interrupt_mode = 0};

    ServoMotorConfig Return_4_Cfg = {.htim_pwm = &htim8,
                                     .channel_number = TIM_CHANNEL_5,
                                     .pulse_min = 0.0005f,  // 0.5ms en secondes
                                     .pulse_max = 0.0025f,  // 2.5ms en secondes
                                     .angle_max = 180.0f,
                                     .interrupt_mode = 0};

    init_servo_motor(&ServoReturn1, &Return_1_Cfg);
    init_servo_motor(&ServoReturn2, &Return_2_Cfg);
    init_servo_motor(&ServoReturn3, &Return_3_Cfg);
    init_servo_motor(&ServoReturn4, &Return_4_Cfg);

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