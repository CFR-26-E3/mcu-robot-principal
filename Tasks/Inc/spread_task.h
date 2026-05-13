//
// Created by maxim on 12/05/2026.
//

#ifndef MCU_ROBOT_PRINCIPAL_ECARTEMENT_TASK_H
#define MCU_ROBOT_PRINCIPAL_ECARTEMENT_TASK_H
#include "cmsis_os.h"
#include "main.h"
enum Commande { SERRE, DESSERRE };

void StartEcartementTask(void *argument);
#endif  // MCU_ROBOT_PRINCIPAL_ECARTEMENT_TASK_H
