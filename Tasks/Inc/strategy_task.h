#ifndef MCU_ROBOT_PRINCIPAL_STRAT_TASK_H
#define MCU_ROBOT_PRINCIPAL_STRAT_TASK_H

#include "cmsis_os.h"
#include "main.h"

typedef struct {
    float x;      // Position en mm
    float y;      // Position en mm
    float angle;  // Orientation en degrés
} Position_t;

#define STRATEGY_TASK_RESUME_FLAG (1 << 0)

#define STRAT_BIT_POSITION (1 << 0)      // Déplacement terminé
#define STRAT_BIT_RETOURNEMENT (1 << 1)  // Mouvement ascenseur terminé
#define STRAT_BIT_DEPOSE (1 << 2)        // Action de serrage terminée
#define STRAT_BIT_CURSEUR (1 << 3)       // Action d'écartement terminée

void StartStrategyTask(void *);
#endif  // MCU_ROBOT_PRINCIPAL_STRAT_TASK_H
