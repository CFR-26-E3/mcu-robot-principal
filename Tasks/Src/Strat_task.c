
#include "Strat_task.h"

void strategie_run() {
    const Position_t points_arret_caisse[] = {
        {1200.0, 800.0, 90.0},  {1200.0, 1500.0, 90.0}, {1200.0, 2200.0, 90.0},
        {1200.0, 2900.0, 90.0}, {1900.0, 2300.0, 270},  {1900.0, 1500.0, 270},
        {1900.0, 700.0, 270},   {1200.0, 100.0, 0.0},   {0.0, 0.0, 0.0}};

    const Position_t points_arret_garde_mange[] = {
        {800.0, 150.0, 0.0},    {1200.0, 1150.0, 90.0}, {1200.0, 1850.0, 90.0},
        {1200.0, 2900.0, 90.0}, {1900.0, 2300.0, 270},  {1900.0, 1500.0, 270},
        {1900.0, 700.0, 270},   {1200.0, 100.0, 0.0},   {0.0, 0.0, 0.0}};

    for (int i = 0; i < 7; i++) {
        // Déplacement

        Position_t destination = points_arret_caisse[i];

        // osMessageQueuePut(QueueMoteur, &destination, 0, osWaitForever);

        // avec QueueMoteur l'identifiant de la file de message (Queue)
        // créée dans CubeMX,0 l'importance mais elles seront tous de le meme
        // importance dans position appart si le cronos arrive à la fin et qu'il
        // faut rentrer. osWaitForever c'est juste que ce qu'il y avait
        // precedement sois fait.
        // la ligne ci-dessus permet de reveiller la tache
        // qui contient : osStatus_t status =
        // osMessageQueueGet(QueueMoteur, &cible, NULL, osWaitForever); ce
        // qui permet de recuperer la cible position_t et donc de faire ... Pour
        // ca la structure dans la tache a reveiller doit etre : if (status ==
        // osOK){}

        osThreadFlagsWait(STRAT_BIT_POSITION, osFlagsWaitAll, osWaitForever);

        // Ascenseur + Serrage + ascenqseur + Ecartement + Return + Ecartement
        float jsp_quoi_encore = 2.0;
        // osMessageQueuePut(QueueRetournement
        // ,&jsp_quoi_encore,0,osWaitForever);

        // Aller au garde mangé
        destination = points_arret_garde_mange[i];
        // osMessageQueuePut(QueueMoteur, &destination, 0, osWaitForever);
        // Transition
        osThreadFlagsWait(STRAT_BIT_RETOURNEMENT | STRAT_BIT_POSITION,
                          osFlagsWaitAll, osWaitForever);

        // Ascenseur + Desserrage + ascenqseur
        float jsp_toujours = 2.0;
        // osMessageQueuePut(QueueDepose ,&jsp_toujours,0,osWaitForever);

        osThreadFlagsWait(STRAT_BIT_DEPOSE, osFlagsWaitAll, osWaitForever);
    }

    int height_curseur = 0;

    // osMessageQueuePut(QueueCurseur,&height_curseur,0,osWaitForever);

    osThreadFlagsWait(STRAT_BIT_CURSEUR, osFlagsWaitAll, osWaitForever);
 // aller a la base
    Position_t destination = {0.0, 0.0, 0.0};

    // osMessageQueuePut(QueueMoteur, &destination, 1, osWaitForever);

}