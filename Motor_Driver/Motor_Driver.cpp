#include "Motor_Driver.hpp"

Motor::Motor()
{
    int forward_pin = 3;
    int backward_pin = 5;

    init_motor();
}

Motor::Motor(int forwardPin, int backwardPin)
{
    forward_pin = forwardPin;
    backward_pin = backwardPin;

    init_motor();        
}

void Motor::init_motor()
{
    pinMode(forward_pin, OUTPUT);
    pinMode(backward_pin, OUTPUT);

    int speed = 0;
}


void Motor::drive(int speed_in)
{
    float speedPercentage = abs(speed_in) / 100;
    int speedVal = speedPercentage * PWM_MAX; 
    analogWrite(forward_pin, speed_in > 0 ? speedVal : 0);
    analogWrite(backward_pin, speed_in > 0 ? 0 : speedVal);
}

// todo: complete motor_drive class
Motor_Driver::Motor_Driver()
{
    left_motor = nullptr;
    right_motor = nullptr;
}

Motor_Driver::Motor_Driver(Motor* leftMotor, Motor* rightMotor)
{
    left_motor = leftMotor;
    right_motor = rightMotor;
}

Motor_Driver::Motor_Driver(int forwardPin_left, int backwardPin_left,
                           int forwardPin_right, int backwardPin_right)
{
    left_motor = new Motor(forwardPin_left, backwardPin_left);
    right_motor = new Motor(forwardPin_right, backwardPin_right);
}