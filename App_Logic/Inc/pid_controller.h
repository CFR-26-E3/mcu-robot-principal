#ifndef MCU_ROBOT_PRINCIPAL_PID_CONTROLLER_H
#define MCU_ROBOT_PRINCIPAL_PID_CONTROLLER_H

typedef struct {
    float kp;
    float ki;
    float kd;

    float prev_error;
    float prev_integral;
    float prev_derivative;

    float alpha; // compris entre 0 et 1 pour le filtrage de la derivée

    float output_min;
    float output_max;
} PIDController;

float compute_pid_controller(PIDController *controller, float setpoint,
                             float measurement, float dt);

void init_pid_controller(PIDController *controller, float kp, float ki,
                         float kd, float alpha, float output_min, float output_max);

#endif  // MCU_ROBOT_PRINCIPAL_PID_CONTROLLER_H
