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
    1.3f  // Distance charactéristique pour le freinage
#define TARGET_THRESHOLD 0.01
#define ROBOT_MAX_ACCELERATION 1.0f
#define ROBOT_JERK 7.0f

#define ROBOT_MIN_ANGULAR_SPEED 0.1f
#define ROBOT_MAX_ANGULAR_SPEED 3.0f
#define CHARACTERISTIC_ANGLE 0.5f
#define ANGLE_THRESHOLD 0.15f
#define ROBOT_MAX_ANGULAR_ACCELERATION 3.60f
#define ROBOT_ANGULAR_JERK 40.47f

#define ANGLE_ECARTEMENT_DESSERRE 5.0f
#define ANGLE_ECARTEMENT_SERRE 180.0f

#define ANGLE_SERRAGE_SERRE 45.0f
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

#define HAUTEUR_BASSE 0.0f
#define HAUTEUR_HAUTE 0.035f
#define DIAMETRE_POULIE 0.0122f
#define PI_VAL 3.14159265f

/*-----------------------------------------
 * Tâches
 *-----------------------------------------*/

// Fréquence des tâches
#define ODOMETRY_TASK_PERIOD 10         // en ms
#define CMD_ROBOT_POSE_TASK_PERIOD 100  // en ms

// Distance stop
#define DISTANCE_SECURITE_DEFAUT 250
#define DETECTION_TASK_PERIODE_INTERFERENCE 20
#define DETECTION_TASK_PERIODE 100   // en ms
#define DETECTION_TIMER_PERIOD 1.0f  // micros
#define SOUND_SPEED 0.00034f         // m/micros

#endif  // MCU_ROBOT_PRINCIPAL_ROBOT_CONFIG_H
