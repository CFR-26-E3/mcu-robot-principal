#ifndef MCU_ROBOT_PRINCIPAL_STRAT_TASK_H
#define MCU_ROBOT_PRINCIPAL_STRAT_TASK_H

#include "cmd_robot_pose_task.h"
#include "cmsis_os.h"
#include "grip_task.h"
#include "spread_task.h"
typedef struct {
    osThreadId_t *grip_task;
    osThreadId_t *lift_task;
    osThreadId_t *spread_task;
    osThreadId_t *flip_task;
    osThreadId_t *cmd_robot_pose_task;
} StrategyTaskParams;

#define STRAT_BIT_POSITION (1 << 0)  // Déplacement terminé
#define STRAT_BIT_FLIP (1 << 1)      // Tache Flip finish
#define STRAT_BIT_LIFT (1 << 2)      // Tache Lift finish
#define STRAT_BIT_GRIP (1 << 3)      // Tache Grip finish
#define STRAT_BIT_SPREAD (1 << 4)    // Tache Spread finish

void StartStrategyTask(void *argument);
#endif  // MCU_ROBOT_PRINCIPAL_STRAT_TASK_H
