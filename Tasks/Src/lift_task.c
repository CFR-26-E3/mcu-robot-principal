#include <math.h>

#include "Strat_task.h"
#include "dc_motor.h"
#include "encoder.h"
#include "lift_task.h"
#include "main.h"
#include "pid_controller.h"
#include "robot_config.h"

extern DcMotor motor_levage;
extern Encoder encoder_levage;
extern PIDController pid_levage;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim4;

extern osMessageQueueId_t QueueAscenseurHandle;
extern osThreadId_t Strat_taskHandle;

static int Commande_Haut_Bas = 1;

#define HAUTEUR_BASSE 0.0f
#define HAUTEUR_HAUTE 0.035f
#define DIAMETRE_POULIE 0.0122f
#define PI_VAL 3.14159265f

void StartAscenseurTask(void *argument) {
    DcMotorConfig moteur_levage_cfg = {.htim_pwm = &htim1,
                                       .channel_number = TIM_CHANNEL_3,
                                       .dir_port_a = DIRA_LEVAGE_GPIO_Port,
                                       .dir_pin_a = DIRA_LEVAGE_Pin,
                                       .dir_port_b = DIRB_LEVAGE_GPIO_Port,
                                       .dir_pin_b = DIRB_LEVAGE_Pin,
                                       .power_scale = 1.0f};
    EncoderConfig encoder_levage_cfg = {.htim = &htim4};

    init_dc_motor(&motor_levage, &moteur_levage_cfg);
    init_encoder(&encoder_levage, &encoder_levage_cfg);
    init_pid_controller(&pid_levage, KP_LEVAGE_POS, KI_LEVAGE_POS,
                        KD_LEVAGE_POS, ALPHA_LEVAGE_POS, MIN_PWM_LEVAGE,
                        MAX_PWM_LEVAGE);

    const float m_per_tick = (DIAMETRE_POULIE * PI_VAL) / TICKS_PER_REV_WHEELS;
    const float dt = (float)ODOMETRY_TASK_PERIOD / 1000.0f;
    float position_cumulee = 0.0f;
    int32_t last_ticks = (int32_t)__HAL_TIM_GET_COUNTER(&htim4);
    int32_t delta = 0;
    while (1) {
        osThreadFlagsWait(1, 0, osWaitForever);
        if (Commande_Haut_Bas == 1) {
            pid_levage.prev_integral = 0;
            while (fabs(HAUTEUR_HAUTE - position_cumulee) > 0.001f) {
                int32_t current_ticks = (int32_t)__HAL_TIM_GET_COUNTER(&htim4);
                delta = current_ticks - last_ticks;

                if (delta > 1400)
                    delta -= 2800;  // Passage arrière (ex: 0 -> 2799)
                if (delta < -1400)
                    delta += 2800;  // Passage avant (ex: 2799 -> 0)

                position_cumulee += (float)delta * m_per_tick;
                last_ticks = current_ticks;

                float power = compute_pid_controller(&pid_levage, HAUTEUR_HAUTE,
                                                     position_cumulee, dt);
                set_dc_motor_pwm(&motor_levage, -power);

                osDelay(ODOMETRY_TASK_PERIOD);
            }
            set_dc_motor_pwm(&motor_levage, 0.0f);
            Commande_Haut_Bas = 2;
            osDelay(500);
        } else if (Commande_Haut_Bas == 2) {
            pid_levage.prev_integral = 0;
            while (fabs(HAUTEUR_BASSE - position_cumulee) > 0.001f) {
                int32_t current_ticks = (int32_t)__HAL_TIM_GET_COUNTER(&htim4);
                delta = current_ticks - last_ticks;

                if (delta > 1400) delta -= 2800;
                if (delta < -1400) delta += 2800;

                position_cumulee += (float)delta * m_per_tick;
                last_ticks = current_ticks;

                float power = compute_pid_controller(&pid_levage, HAUTEUR_BASSE,
                                                     position_cumulee, dt);
                set_dc_motor_pwm(&motor_levage, -power);

                osDelay(ODOMETRY_TASK_PERIOD);
            }

            set_dc_motor_pwm(&motor_levage, 0.0f);
            Commande_Haut_Bas = 1;
            osDelay(500);
        }
        // osThreadFlagsSet(*argument->, 1);
    }
}
