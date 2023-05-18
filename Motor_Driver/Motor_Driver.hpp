#ifndef MOTOR_DRIVERS
#define MOTOR_DRIVERS

#include "Arduino.h"

#define PWM_MAX 255

class Motor {
    private:
        int forward_pin, backward_pin;
        int speed;
        
        void init_motor();

    public:
        Motor();
        Motor(int forwardPin, int backwardPin);
        void drive(int speed_in);
};

class Motor_Driver {
    private:
        Motor* left_motor;
        Motor* right_motor;
        
    public:
        Motor_Driver();
        Motor_Driver(Motor* leftMotor, Motor* rightMotor);
        Motor_Driver(int forwardPin_left, int backwardPin_left,
                     int forwardPin_right, int backwardPin_right);
        
        void drive(int speed_in_left, int speed_in_right);
        void drive(int speeds[2]);
};

#endif MOTOR_DRIVERS