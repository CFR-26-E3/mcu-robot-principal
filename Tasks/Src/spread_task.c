//
// Created by maxim on 11/05/2026.
//

#include "spread_task.h"

#include "strategy_task.h"

typedef struct {
    float angle;
} CommandeServoSpread;

CommandeServoSpread CommandeSpread[2] = {{ANGLE_ECARTEMENT_DESSERRE},
                                         {ANGLE_ECARTEMENT_SERRE}};

static enum CmdSpread CommandeImpose;
static osMutexId_t CommandeImpose_mutex;

void StartSpreadTask(void* argument) {
    SpreadTaskParams* params = (SpreadTaskParams*)(argument);

    CommandeImpose_mutex = osMutexNew(NULL);

    CommandeImpose = CommandeSpread[RAPPROCHE].angle;
    set_servo_angle(&params->SpreadServo, CommandeImpose);

    float angle;

    while (1) {
        osThreadFlagsWait(1, 0, osWaitForever);

        angle = CommandeSpread[RAPPROCHE].angle;
        if (osMutexAcquire(CommandeImpose_mutex, 2) == osOK) {
            angle = CommandeSpread[CommandeImpose].angle;
            osMutexRelease(CommandeImpose_mutex);
        }

        set_servo_angle(&params->SpreadServo, angle);

        osThreadFlagsSet(*params->strategy_task, STRAT_BIT_SPREAD);
    }
}

void Set_spread_angle(enum CmdSpread i) {
    if (osMutexAcquire(CommandeImpose_mutex, 2) == osOK) {
        CommandeImpose = i;
        osMutexRelease(CommandeImpose_mutex);
    }
}
