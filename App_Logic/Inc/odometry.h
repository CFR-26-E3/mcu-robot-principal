#ifndef MCU_ROBOT_PRINCIPAL_ODOMETRY_H
#define MCU_ROBOT_PRINCIPAL_ODOMETRY_H

#include "math.h"
#include "planar-computation.h"
#include "robot_config.h"
#include "robot_types.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

void ComputePose(Pose2D *pose, int left_ticks_delta, int right_ticks_delta);

#endif  // MCU_ROBOT_PRINCIPAL_ODOMETRY_H
