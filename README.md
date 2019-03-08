# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---
<p align="center">
<a href="https://www.youtube.com/watch?v=ThtW1yGziS0"><img src="./pid_control.gif" alt="PID Control" width="70%" height="70%">
</a>
<br> PID Control
</p>


## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

Fellow students have put together a guide to Windows set-up for the project [here](https://s3-us-west-1.amazonaws.com/udacity-selfdrivingcar/files/Kidnapped_Vehicle_Windows_Setup.pdf) if the environment you have set up for the Sensor Fusion projects does not work for this project. There's also an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3).

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Implementation
This implementation of PID control includes editing of below files
1. `PID.h`
2. `PID.cpp`
3. `main.cpp`
4. Creation of `car_control.cpp`

Now let's see the details operations we did on every file.
1. `PID.h`
	This file has declaration of class PID. Also it declares its default constructor and destructor. Getters and setters are written since veriables were declared private.
It also declares some new functions named and used as below:
* `Init()`: This initializes the `p`, `i` and `d` coefficients.
* `UpdateError()`: This is for update of `p`, `i` and `d` errors.
* `TotalError()`: This function returns the total error calculated by PID controller which will be used as a `steer_value` in `main.cpp` to steer the vehicle to correct path.

2. `PID.cpp`
	This file is having definition of all the declared functionalities in `PID.h`. It also initializes the `p`, `i` and `d` error to `0.0`.

3. `main.cpp`:
	This file handles the communication with simulator. Also, it is responsible to send the `steer_value` to the vehicle in simulator and receive data from it like `cte` (Cross Track Error), `speed` of the vehicle and `angle` of the vehicle.
This file uses `PID.h` and `PID.cpp` along with `car_control.cpp` to drive the vehicle along the path in simulator.

4. `car_control.cpp`:
	This file is for calculation of `throttle` value for the vehicle which moves it further in the simulator.
	This takes in 3 arguments as `cte`, `angle`, `speed` of the vehicle. Then with below logic, it gives positive or negative throttle.
```cpp
double get_throttle(double cte, double angle, double speed){
  double throttle;
  if (speed < 80 && abs(cte) < 0.5 && angle < 2) {
  // To achieve maximum speed, we're giving 95% of the throttle when car is moving in straight direction.
        throttle = 0.95;
      }
  else if (abs(cte) > 0.5 || abs(angle) > 0.15)
  // If the cte and angle are big, then we either give no throttle or if the speed is also large, we apply brakes.
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
  // If cte is very big i.e, more than 1, then we only apply brakes with more power so that it will lower down the vehicle speed.
  {
    throttle = -0.2;
  }
  return throttle;
}
```

* Using above mentioned logic, we're applying brakes whenever the vehicle is taking turns, or if it's not able to get `cte` nearly equal to 0.
* This helps to keep the `cte