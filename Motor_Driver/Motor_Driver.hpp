#ifndef MOTOR_DRIVERS
#define MOTOR_DRIVERS

#include "Arduino.h"

#define PWM_MAX 255

class Motor {
    public:
        int forward_pin, backward_pin;
        int speed;

    private:
        Motor(int forwardPin, int backwardPin);
        void drive(int speed_in);
};

class Motor_Driver {
    public:
        Motor left_motor, right_motor;
        
    private:
        Motor_Driver (Motor leftMotor, Motor rightMotor);
        Motor_Driver (int forwardPin_left, int backwardPin_left,
                      int forwardPin_right, int backwardPin_right);
        
        void drive(int speed_in_left, int speed_in_right);
        void drive(int speeds[2]);
};

#endif MOTOR_DRIVERS