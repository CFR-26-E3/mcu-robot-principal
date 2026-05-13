#ifndef MCU_ROBOT_PRINCIPAL_ROBOT_CONFIG_H
#define MCU_ROBOT_PRINCIPAL_ROBOT_CONFIG_H

/*-----------------------------------------
 * Dimensions physique du robot
 *-----------------------------------------*/

#define WHEEL_RADIUS 0.05f  // Rayon des roues en mètres
#define WHEELS_BASE 0.308f  // Distance entre les roues en mètres

#define TICKS_PER_REV_WHEELS 2800  // Ticks par tour des encodeurs

#define GT2_PULLEY_DIAMETER 0.01269
#define STEPS_PER_METER 10033.3333
#define METERS_PER_STEP 0.0000996678

/*-----------------------------------------
 * Paramètres de contrôle
 *-----------------------------------------*/

// Limites de vitesse
#define ROBOT_MIN_SPEED 0.05f
#define ROBOT_MAX_SPEED 0.8f
#define CHARACTERISTIC_DISTANCE \
    1.0f  // Distance charactéristique pour le freinage
#define TARGET_THRESHOLD 0.01
#define ROBOT_MAX_ACCELERATION 0.4f
#define ROBOT_JERK 5.0f

#define ROBOT_MIN_ANGULAR_SPEED 0.1f
#define ROBOT_MAX_ANGULAR_SPEED 1.0f
#define CHARACTERISTIC_ANGLE 0.5f
#define ANGLE_THRESHOLD 0.05f
#define ROBOT_MAX_ANGULAR_ACCELERATION 2.60f
#define ROBOT_ANGULAR_JERK 32.47f

#define ANGLE_ECARTEMENT_SERRE 0.0f
#define ANGLE_ECARTEMENT_DESSERRE 110.0f

#define ANGLE_SERRAGE_SERRE 60.0f
#define ANGLE_SERRAGE_DESSERRE 100.0f
// PID moteurs droit et gauche
#define KP_WHEELS_MOTOR 3.0f
#define KI_WHEELS_MOTOR 0.1f
#define KD_WHEELS_MOTOR 0.0f
#define ALPHA_WHEELS_MOTOR 0.0f
#define MAX_PWM_OUTPUT 1.0f
#define MIN_PWM_OUTPUT (-1.0f)

// PID moteur levage pince

#define KP_LEVAGE_POS 20.0f
#define KI_LEVAGE_POS 0.50f
#define KD_LEVAGE_POS 0.0f
#define ALPHA_LEVAGE_POS 0.0f
#define MAX_PWM_LEVAGE 0.6f  // On bride à 60% pour la sécurité
#define MIN_PWM_LEVAGE (-0.6f)

/*-----------------------------------------
 * Tâches
 *-----------------------------------------*/

// Fréquence des tâches
#define ODOMETRY_TASK_PERIOD 10         // en ms
#define CMD_ROBOT_POSE_TASK_PERIOD 100  // en ms

#endif  // MCU_ROBOT_PRINCIPAL_ROBOT_CONFIG_H
