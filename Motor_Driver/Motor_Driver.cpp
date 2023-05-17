#include "Motor_Driver.hpp"

Motor::Motor(int forwardPin, int backwardPin)
{
    forward_pin = forwardPin;
    backward_pin = backwardPin;

    pinMode(forward_pin, OUTPUT);
    pinMode(backward_pin, OUTPUT);

    speed = 0;            
}


void Motor::drive(int speed_in)
{
    float speedPercentage = abs(speed_in) / 100;
    int speedVal = speedPercentage * PWM_MAX; 
    analogWrite(forward_pin, speed_in > 0 ? speedVal : 0);
    analogWrite(backward_pin, speed_in > 0 ? 0 : speedVal);
}

// todo: complete motor_drive class