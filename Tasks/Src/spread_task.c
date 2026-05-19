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

static enum CmdSpread CommandeImposes;
static osMutexId_t CommandeImposes_mutex;

void StartSpreadTask(void* argument) {
    SpreadTaskParams* params = (SpreadTaskParams*)(argument);

    CommandeImposes_mutex = osMutexNew(NULL);

    CommandeImposes = CommandeSpread[RAPPROCHE].angle;
    set_servo_angle(&params->SpreadServo, CommandeImposes);

    float angle;

    while (1) {
        osThreadFlagsWait(1, 0, osWaitForever);

        angle = CommandeSpread[RAPPROCHE].angle;
        if (osMutexAcquire(CommandeImposes_mutex, 2) == osOK) {
            angle = CommandeSpread[CommandeImposes].angle;
            osMutexRelease(CommandeImposes_mutex);
        }

        set_servo_angle(&params->SpreadServo, angle);

        osThreadFlagsSet(*params->strategy_task, STRAT_BIT_SPREAD);
    }
}

void Set_spread_angle(enum CmdSpread i) {
    if (osMutexAcquire(CommandeImposes_mutex, 2) == osOK) {
        CommandeImposes = i;
        osMutexRelease(CommandeImposes_mutex);
    }
}
