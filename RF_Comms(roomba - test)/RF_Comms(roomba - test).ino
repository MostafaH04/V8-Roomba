#include "Motor_Driver.hpp"
#include "Onboard_Comms.hpp"
#include "RF_Comms.hpp"

//Slave
int motorPins[MOTOR_ROWS][MOTOR_COLS][NUM_MOTOR_PINS];
Motor_Driver testDriver;
CommsIn comms;
void receivedData(int numBytes)
{
  comms.commsRecieved(numBytes);
}

//RF comms test code
//Receiver: Receives data from the dock

dataOut_t test_in;
test_in.US_reading_1 = 55.0;
test_in.US_reading_2 = 66.0;
test_in.x_pos = 7.0;
test_in.y_pos = 8.0;
test_in.z_pos = 9.0;
test_in.roomba_state = 2;
test_in.roomba_tx_address = "00002";

Rf_Comms test_comms_in;

void setup() {
  Wire.begin(SLAVE_ADDR);

  test_comms.initAddress();
  test_comms.init();

  test_comms.Bot_sendData(test_in);
  Serial.println("Data sent from roomba");
  delay(1000);
}

void loop()
{
  // test_out not declared
  test_comms.Bot_readData(test_out);
  Serial.println("Data received from dock");
  delay(1000);
}
