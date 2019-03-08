#include "PID.h"
#include <iostream>

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {
  p_error = 0.0;
  i_error = 0.0;
  d_error = 0.0;
}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  set_Kp(Kp_);
  set_Ki(Ki_);
  set_Kd(Kd_);
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
    i_error  += cte;
    d_error  = cte - p_error;
    p_error  = cte;
}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  return -(get_Kp() * p_error + get_Ki() * i_error + get_Kd() * d_error);
}
