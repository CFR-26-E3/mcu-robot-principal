#include "odometry.h"

void ComputePose(Pose2D *pose, int left_ticks_delta, int right_ticks_delta) {
    const float left_delta = 2.0f * (float)M_PI * WHEEL_RADIUS *
                             (float)left_ticks_delta /
                             (float)TICKS_PER_REV_WHEELS;
    const float right_delta = 2.0f * (float)M_PI * WHEEL_RADIUS *
                              (float)right_ticks_delta /
                              (float)TICKS_PER_REV_WHEELS;

    const float center_delta = (right_delta + left_delta) / 2.0f;
    const float delta_theta = (right_delta - left_delta) / WHEELS_BASE;

    pose->x += center_delta * cosf(pose->theta + delta_theta / 2.0f);
    pose->y += center_delta * sinf(pose->theta + delta_theta / 2.0f);
    pose->theta += delta_theta;

    if (pose->theta > M_PI) pose->theta -= 2.0f * M_PI;
    if (pose->theta < -M_PI) pose->theta += 2.0f * M_PI;
}
