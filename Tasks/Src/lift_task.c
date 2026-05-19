
#include "lift_task.h"

#include "strategy_task.h"

PIDController pid_levage;

static int Commande_Haut_Bas = 1;

void StartLiftTask(void* argument) {
    LiftTaskParams* params = (LiftTaskParams*)(argument);

    init_pid_controller(&pid_levage, KP_LEVAGE_POS, KI_LEVAGE_POS,
                        KD_LEVAGE_POS, ALPHA_LEVAGE_POS, MIN_PWM_LEVAGE,
                        MAX_PWM_LEVAGE);

    const float m_per_tick = (DIAMETRE_POULIE * PI_VAL) / TICKS_PER_REV_WHEELS;
    const float dt = (float)ODOMETRY_TASK_PERIOD / 1000.0f;
    float position_cumulee = 0.0f;
    int32_t last_ticks = get_encoder_ticks(&params->encoder_levage);
    int32_t delta = 0;
    while (1) {
        osThreadFlagsWait(1, 0, osWaitForever);
        if (Commande_Haut_Bas == 1) {
            pid_levage.prev_integral = 0;
            while (fabs(HAUTEUR_HAUTE - position_cumulee) > 0.002f) {
                int32_t current_ticks =
                    get_encoder_ticks(&params->encoder_levage);
                delta = current_ticks - last_ticks;

                if (delta > 1400)
                    delta -= 2800;  // Passage arrière (ex: 0 -> 2799)
                if (delta < -1400)
                    delta += 2800;  // Passage avant (ex: 2799 -> 0)

                position_cumulee += (float)delta * m_per_tick;
                last_ticks = current_ticks;

                float power = compute_pid_controller(&pid_levage, HAUTEUR_HAUTE,
                                                     position_cumulee, dt);
                if (fabs(power) < 0.15) {
                    position_cumulee = HAUTEUR_HAUTE;
                }
                set_dc_motor_pwm(&params->motor_levage, -power);

                osDelay(ODOMETRY_TASK_PERIOD);
            }
            set_dc_motor_pwm(&params->motor_levage, 0.0f);
            Commande_Haut_Bas = 2;
            osDelay(500);
        } else if (Commande_Haut_Bas == 2) {
            pid_levage.prev_integral = 0;
            while (fabs(HAUTEUR_BASSE - position_cumulee) > 0.01f) {
                int32_t current_ticks =
                    get_encoder_ticks(&params->encoder_levage);
                delta = current_ticks - last_ticks;

                if (delta > 1400) delta -= 2800;
                if (delta < -1400) delta += 2800;

                position_cumulee += (float)delta * m_per_tick;
                last_ticks = current_ticks;

                float power = compute_pid_controller(&pid_levage, HAUTEUR_BASSE,
                                                     position_cumulee, dt);
                if (fabs(power) < 0.15) {
                    position_cumulee = HAUTEUR_BASSE;
                }
                set_dc_motor_pwm(&params->motor_levage, -power);

                osDelay(ODOMETRY_TASK_PERIOD);
            }

            set_dc_motor_pwm(&params->motor_levage, 0.0f);
            Commande_Haut_Bas = 1;
            osDelay(500);
        }
        osThreadFlagsSet(*params->strategy_task, STRAT_BIT_LIFT);
    }
}
