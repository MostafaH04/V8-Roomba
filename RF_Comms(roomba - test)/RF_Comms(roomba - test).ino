#include "Motor_Driver.hpp"
#include "Onboard_Comms.hpp"

//Slave
int motorPins[MOTOR_ROWS][MOTOR_COLS][NUM_MOTOR_PINS];
Motor_Driver testDriver;


CommsIn comms;


void receivedData(int numBytes)
{
  comms.commsRecieved(numBytes);
}

void setup()
{
  Wire.begin(SLAVE_ADDR);
}

void loop()
{
    
}