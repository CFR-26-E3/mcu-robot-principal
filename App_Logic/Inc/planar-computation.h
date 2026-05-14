#ifndef PLANAR_COMPUTATION_LIBRARY_H
#define PLANAR_COMPUTATION_LIBRARY_H

#include <math.h>
#include <stdint.h>

/**
 * @brief Pose 2D du robot.
 */
typedef struct {
    float x;      // Position x en m
    float y;      // Position y en m
    float theta;  // Cap en rad
} Pose2D;

uint8_t pose2d_are_equals(const Pose2D* a, const Pose2D* b);

/**
 * Computes the Euclidian distance in meters between tow points.
 * @param a The position of the first point
 * @param b The position of the second point
 * @return The distance between the two points in meters.
 */
extern float ComputeL2Distance(Pose2D a, Pose2D b);

/**
 * Computes the angle in radians from the angle of the starting point to the
 * target
 * @param start The position of the starting point
 * @param goal The position of the goal point
 * @return The angle in radians.
 */
extern float ComputeAngleToPath(Pose2D start, Pose2D goal);

/**
 * Add the two positions term-by-term
 * @param a Position a
 * @param b Position b
 * @return The sum of the two positions
 */
extern Pose2D AddPositions(Pose2D a, Pose2D b);

/**
 * Keeps the angle between 0 and 2*PI.
 * @param angle The angle to be conditioned
 * @return The angle conditioned
 */
extern float ConditionedAngle(float angle);

#endif  // PLANAR_COMPUTATION_LIBRARY_H
