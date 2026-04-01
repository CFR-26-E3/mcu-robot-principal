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
#define MAX_LINEAR_VELOCITY 1.0f   // Vitesse linéaire maximale en m/s
#define MAX_ANGULAR_VELOCITY 1.0f  // Vitesse angulaire maximale en rad/s

// PID moteurs droit et gauche
#define KP_WHEELS_MOTOR 3.0f
#define KI_WHEELS_MOTOR 0.1f
#define KD_WHEELS_MOTOR 0.0f
#define ALPHA_WHEELS_MOTOR 0.0f
#define MAX_PWM_OUTPUT 1.0f
#define MIN_PWM_OUTPUT (-1.0f)

// PID moteur levage pince

/*-----------------------------------------
 * Tâches
 *-----------------------------------------*/

// Fréquence des tâches
#define ODOMETRY_TASK_PERIOD 10         // en ms
#define CMD_ROBOT_POSE_TASK_PERIOD 100  // en ms

#endif  // MCU_ROBOT_PRINCIPAL_ROBOT_CONFIG_H
