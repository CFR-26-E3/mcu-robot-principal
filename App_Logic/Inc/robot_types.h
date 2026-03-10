#ifndef MCU_ROBOT_PRINCIPAL_ROBOT_TYPES_H
#define MCU_ROBOT_PRINCIPAL_ROBOT_TYPES_H

/**
 * @brief Pose 2D du robot.
*/
typedef struct {
    float x;       /**< Position x en m */
    float y;       /**< Position y en m */
    float theta;   /**< Cap en rad */
} Pose2D;

#endif  // MCU_ROBOT_PRINCIPAL_ROBOT_TYPES_H
