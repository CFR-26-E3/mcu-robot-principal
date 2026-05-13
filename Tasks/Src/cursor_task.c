#include "cursor_task.h"

#include "servo_motor.h"
void StartCurseurTask(void *argument) {
    int commande;
    ServoConfig curseurServo = {&htim8, TIM_CHANNEL_1, 0.5f, 2.5f};
    SERVO_Init(&curseurServo);
    SERVO_SetAngle(&curseurServo, 0.0f);
    while (1) {
        // osMessageQueueGet(QueueCurseurHandle, &commande,NULL, osWaitForever);

        if (commande == 1) {
            SERVO_SetAngle(&curseurServo, 180.0f);
        } else {
            SERVO_SetAngle(&curseurServo, 0.0f);
        }

        osDelay(500);  // Laisse le temps au servo de bouger

        // Liberer la tache en mettant le bit STRAT_BIT_CURSEUR A 1
        // osThreadFlagsSet(Strat_taskHandle, STRAT_BIT_CURSEUR);
    }
}
