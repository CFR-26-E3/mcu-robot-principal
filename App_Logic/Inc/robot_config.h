#ifndef MCU_ROBOT_PRINCIPAL_ROBOT_CONFIG_H
#define MCU_ROBOT_PRINCIPAL_ROBOT_CONFIG_H

/*-----------------------------------------
 * Dimensions physique du robot
 *-----------------------------------------*/

#define WHEEL_RADIUS 0.05f  // Rayon des roues en mètres
#define WHEEL_BASE 0.3f     // Distance entre les roues en mètres

#define TICKS_PER_REV_WHEELS 2800  // Ticks par tour des encodeurs des roues

/*-----------------------------------------
 * Paramètres de contrôle
 *-----------------------------------------*/

// Limites de vitesse
#define MAX_LINEAR_VELOCITY 1.0f   // Vitesse linéaire maximale en m/s
#define MAX_ANGULAR_VELOCITY 1.0f  // Vitesse angulaire maximale en rad/s

// PID moteurs droit et gauche

// PID moteur levage pince

/*-----------------------------------------
 * Tâches
 *-----------------------------------------*/

#define ODOMETRY_PERIOD 10  // Période d'échantillonnage de l'odométrie en ms

#endif  // MCU_ROBOT_PRINCIPAL_ROBOT_CONFIG_H
