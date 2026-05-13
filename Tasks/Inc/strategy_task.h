#ifndef MCU_ROBOT_PRINCIPAL_STRAT_TASK_H
#define MCU_ROBOT_PRINCIPAL_STRAT_TASK_H

#include "cmsis_os.h"
#include "main.h"

typedef struct {
    float x;      // Position en mm
    float y;      // Position en mm
    float angle;  // Orientation en degrés
} Position_t;

#define STRAT_BIT_POSITION (1 << 0)  // Déplacement terminé
#define STRAT_BIT_FLIP (1 << 1)      // Mouvement ascenseur terminé
#define STRAT_BIT_LIFT (1 << 2)      // Action de serrage terminée
#define STRAT_BIT_GRIP (1 << 3)      // Action d'écartement terminée
#define STRAT_BIT_GRIP (1 << 3)      // Action d'écartement terminée

void strategie_run(void);
#endif  // MCU_ROBOT_PRINCIPAL_STRAT_TASK_H
