#include "pid_controller.h"

void init_pid_controller(PIDController *controller, float kp, float ki,
                         float kd, float alpha, float output_min,
                         float output_max) {
    controller->kp = kp;
    controller->ki = ki;
    controller->kd = kd;
    controller->prev_error = 0.0f;
    controller->prev_integral = 0.0f;
    controller->prev_derivative = 0.0f;

    controller->alpha = alpha;

    controller->output_min = output_min;
    controller->output_max = output_max;
}

float compute_pid_controller(PIDController *controller, float setpoint,
                             float measurement, float dt) {
    float error = setpoint - measurement;

    float proportional_out = controller->kp * error;
    float integral_out =
        controller->prev_integral + controller->ki * error * dt;
    float new_deriv = (error - controller->prev_error) / dt;

    float deriv_filtered =
        controller->alpha * new_deriv +
        (1 - controller->alpha) * controller->prev_derivative;
    float output =
        proportional_out + integral_out + controller->kd * deriv_filtered;

    if (output >
        controller->output_max) {  // On s'assure que la sortie reste acceptable
        output = controller->output_max;
    } else if (output < controller->output_min) {
        output = controller->output_min;
    }
    // on enregistre les variables la prochaine iteration
    controller->prev_error = error;
    controller->prev_integral = integral_out;
    controller->prev_derivative = deriv_filtered;
    return output;
}
