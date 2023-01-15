#define MOTOR_ROWS 1

#include "Onboard_Comms.hpp"

//Master
CommsOut comms;
void setup()
{
    Serial.begin(9600);
    comms = CommsOut(SLAVE_ADDR);
}

void loop()
{
}