
#include "strategy_task.h"

#include "main.h"

void StartStrategyTask(void* argument) {
    StrategyTaskParams* params = (StrategyTaskParams*)(argument);

    const Pose2D points_arret_caisse[] = {
        {1.2, 0.8, 90.0},  {1.2, 1.5, 90.0},  {1.2, 2.2, 90.0},
        {1.2, 2.9, 90.0},  {1.9, 2.3, 270.0}, {1.9, 1.5, 270.0},
        {1.9, 0.7, 270.0}, {1.2, 0.1, 0.0},   {0.0, 0.0, 0.0}};

    const Pose2D points_arret_garde_mange[] = {
        {0.8, 0.15, 0.0},  {1.2, 1.15, 90.0}, {1.2, 1.85, 90.0},
        {1.2, 2.9, 90.0},  {1.9, 2.3, 270.0}, {1.9, 1.5, 270.0},
        {1.9, 0.7, 270.0}, {1.2, 0.1, 0.0},   {0.0, 0.0, 0.0}};

    SetPoseTarget((Pose2D){45.0, 0.0, 0.0});
    // Destination tout droit devant les caisses
    osThreadFlagsWait(STRAT_BIT_POSITION, osFlagsWaitAll, osWaitForever);

    SetPoseTarget((Pose2D){0.0, 0.0, 0.0});
    // Destination tout droit devant les caisses
    osThreadFlagsWait(STRAT_BIT_POSITION, osFlagsWaitAll, osWaitForever);
    // On attend d'être arrivé
    // !!!! force-t-on l'angle a 90 si on veut faire ligne droite

    /*
    for (int i = 0; i < 7; i++) {
        // Déplacement
        SetPoseTarget(points_arret_caisse[i]);
        // Destination tout droit devant les caisses
        osThreadFlagsWait(STRAT_BIT_POSITION, osFlagsWaitAll, osWaitForever);

        // fermer écartement
        osThreadFlagsSet(*params->lift_task, 1);
        // descendre lift
        osThreadFlagsWait(STRAT_BIT_LIFT, osFlagsWaitAll, osWaitForever);

        Set_grip_angle(SERRE);
        osThreadFlagsSet(*params->grip_task, 1);
        // Fermer pince
        osThreadFlagsWait(STRAT_BIT_GRIP, osFlagsWaitAll, osWaitForever);

        osThreadFlagsSet(*params->lift_task, 1);
        // monter lift
        osThreadFlagsWait(STRAT_BIT_LIFT, osFlagsWaitAll, osWaitForever);

        // On commence à se déplacer et après on écarte et flip
        SetPoseTarget(points_arret_garde_mange[i]);
        // On va vers la zone verte centrale de notre coté

        Set_grip_angle(ECARTE);
        osThreadFlagsSet(*params->spread_task, 1);
        // écarter caisses
        osThreadFlagsWait(STRAT_BIT_SPREAD, osFlagsWaitAll, osWaitForever);

        // mutex a mettre
        osThreadFlagsSet(*params->flip_task, 1);
        // écarter caisses
        osThreadFlagsWait(STRAT_BIT_FLIP, osFlagsWaitAll, osWaitForever);

        Set_grip_angle(RAPPROCHE);
        osThreadFlagsSet(*params->spread_task, 1);

        osThreadFlagsWait(STRAT_BIT_POSITION | STRAT_BIT_SPREAD, osFlagsWaitAll,
                          osWaitForever);
        osThreadFlagsSet(*params->lift_task, 1);
        osThreadFlagsWait(STRAT_BIT_LIFT, osFlagsWaitAll, osWaitForever);

        Set_grip_angle(DESSERRE);
        osThreadFlagsSet(*params->grip_task, 1);
        // Fermer pince
        osThreadFlagsWait(STRAT_BIT_GRIP, osFlagsWaitAll, osWaitForever);

        osThreadFlagsSet(*params->lift_task, 1);
        osThreadFlagsWait(STRAT_BIT_LIFT, osFlagsWaitAll, osWaitForever);
    }
    */

    while (1) {
    }
}