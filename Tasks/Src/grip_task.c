//
// Created by maxim on 11/05/2026.
//

#include "grip_task.h"

typedef struct {
    float angle;
} CommandeServoGrip;

CommandeServoGrip CommandeGrip[2] = {{ANGLE_SERRAGE_SERRE},
                                     {ANGLE_SERRAGE_DESSERRE}};

static enum CmdGrip CommandeImpose;
static osMutexId_t CommandeImpose_mutex;

void StartGripTask(void* argument) {
    GripTaskParams* params = (GripTaskParams*)(argument);
    CommandeImpose = CommandeGrip[1].angle;
    set_servo_angle(&params->GripServo, CommandeImpose);
    float angle;
    while (1) {
        osThreadFlagsWait(1, 0, osWaitForever);
        angle = CommandeGrip[1].angle;
        set_servo_angle(&params->GripServo, angle);
        osDelay(500);
        if (osMutexAcquire(CommandeImpose_mutex, 2) == osOK) {
            angle = CommandeGrip[CommandeImpose].angle;
            osMutexRelease(CommandeImpose_mutex);
        }
        set_servo_angle(&params->GripServo, angle);
        osDelay(500);
        osThreadFlagsSet(*params->strategy_task, 1);
    }
}

void Set_grip_angle(enum CmdGrip i) {
    if (osMutexAcquire(CommandeImpose_mutex, 2) == osOK) {
        CommandeImpose = i;
        osMutexRelease(CommandeImpose_mutex);
    }
}
