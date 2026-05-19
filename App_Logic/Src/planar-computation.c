#include "planar-computation.h"

float ComputeL2Distance(const Pose2D a, const Pose2D b) {
    return sqrtf(powf((a.x - b.x), 2) + powf((a.y - b.y), 2));
}

float ComputeAngleToPath(const Pose2D start, const Pose2D goal) {
    float path_angle = atanf((goal.y - start.y) / (goal.x - start.x));
    path_angle = goal.x - start.x > 0 ? path_angle : M_PI + path_angle;
    float angle_to_path = path_angle - start.theta;
    return ConditionedAngle(angle_to_path);
}

Pose2D AddPositions(Pose2D a, Pose2D b) {
    Pose2D result = {};
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.theta = a.theta + b.theta;
    return result;
}

float ConditionedAngle(float angle) {
    if (angle > M_PI) return angle - 2 * M_PI;
    if (angle < -M_PI) return angle + 2 * M_PI;
    return angle;
}

uint8_t pose2d_are_equals(const Pose2D* a, const Pose2D* b) {
    return (a->x != b->x) || (a->y != b->y) || (a->theta != b->theta);
}

