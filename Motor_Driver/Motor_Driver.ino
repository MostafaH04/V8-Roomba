#include "Motor_Driver.hpp"

Motor_Driver driver;

void setup()
{
    Serial.begin(9600);    
    Motor* motor_left = new Motor(3, 5);
    Motor* motor_right = new Motor(9,10);
    
    driver = Motor_Driver(motor_left,  motor_right);
}

void loop()
{
    for (int speedLeft = -100; speedLeft < 100; speedLeft ++)
    {
        for (int speedRight = -100; speedRight < 100; speedRight ++)
        {
            driver.drive(speedLeft, speedRight);
            delay(50);
        }
    }
}
