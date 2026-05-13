
#include "strategy_task.h"

void StartStrategyTask(void* argument) {
    StrategyTaskParams* params = (StrategyTaskParams*)(argument);

    const Pose2D points_arret_caisse[] = {
        {1200.0, 800.0, 90.0},  {1200.0, 1500.0, 90.0}, {1200.0, 2200.0, 90.0},
        {1200.0, 2900.0, 90.0}, {1900.0, 2300.0, 270},  {1900.0, 1500.0, 270},
        {1900.0, 700.0, 270},   {1200.0, 100.0, 0.0},   {0.0, 0.0, 0.0}};

    const Pose2D points_arret_garde_mange[] = {
        {800.0, 150.0, 0.0},    {1200.0, 1150.0, 90.0}, {1200.0, 1850.0, 90.0},
        {1200.0, 2900.0, 90.0}, {1900.0, 2300.0, 270},  {1900.0, 1500.0, 270},
        {1900.0, 700.0, 270},   {1200.0, 100.0, 0.0},   {0.0, 0.0, 0.0}};

    Set_target((Pose2D){600.0, 0.0, 0.0});
    // Destination tout droit devant les caisses
    osThreadFlagsWait(STRAT_BIT_POSITION, osFlagsWaitAll, osWaitForever);
    // On attend d'être arrivé
    // !!!! force-t-on l'angle a 90 si on veut faire ligne droite

    for (int i = 0; i < 7; i++) {
        // Déplacement
        Set_target(points_arret_caisse[i]);
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
        Set_target(points_arret_garde_mange[i]);
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
}