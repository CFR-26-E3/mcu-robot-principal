//
// Created by maxim on 11/05/2026.
//

#include "spread_task.h"

typedef struct {
    float angle;
} CommandeServoSpread;

CommandeServoSpread CommandeSpread[2] = {{ANGLE_ECARTEMENT_SERRE},
                                         {ANGLE_ECARTEMENT_DESSERRE}};

static enum CmdSpread CommandeImpose;
static osMutexId_t CommandeImpose_mutex;

void StartSpreadTask(void* argument) {
    SpreadTaskParams* params = (SpreadTaskParams*)(argument);
    CommandeImpose = CommandeSpread[1].angle;
    set_servo_angle(&params->SpreadServo, CommandeImpose);
    float angle;
    while (1) {
        osThreadFlagsWait(1, 0, osWaitForever);
        angle = CommandeSpread[1].angle;
        set_servo_angle(&params->SpreadServo, angle);
        osDelay(500);
        if (osMutexAcquire(CommandeImpose_mutex, 2) == osOK) {
            angle = CommandeSpread[CommandeImpose].angle;
            osMutexRelease(CommandeImpose_mutex);
        }
        set_servo_angle(&params->SpreadServo, angle);
        osDelay(500);
        osThreadFlagsSet(*params->strategy_task, 1);
    }
}

void Set_spread_angle(enum CmdSpread i) {
    if (osMutexAcquire(CommandeImpose_mutex, 2) == osOK) {
        CommandeImpose = i;
        osMutexRelease(CommandeImpose_mutex);
    }
}
