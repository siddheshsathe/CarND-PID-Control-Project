#include <iostream>

double get_throttle(double cte, double angle, double speed){
  /**
   * get_throttle returns the throttle value for the vehicle depending on args
   * @param cte (double) : Cross Track Error. Large value depicts vehicle is 
   *                      away from center of the road
   * @param angle (double) : angle at which vehicle is heading. Straight is 0.
   * @param speed (double) : speed of the vehicle
   * @returns throttle (double) : throttle value to move vehicle forward
   *                              or backward
  */
  double throttle;
  if (speed < 80 && abs(cte) < 0.5 && angle < 2) {
        throttle = 0.95;
      }
  else if (abs(cte) > 0.5 || abs(angle) > 0.15)
  {
    if (speed > 30) {
      throttle = -0.1;
    }
    else
    {
      throttle = 0;
    }
  }
  else if (abs(cte) > 1 || abs(angle) > 0.5)
  {
    throttle = -0.2;
  }
  return throttle;
}