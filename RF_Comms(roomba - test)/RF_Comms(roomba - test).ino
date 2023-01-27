#include "Motor_Driver.hpp"
#include "Onboard_Comms.hpp"
#include "RF_Comms.hpp"

//Slave *EDIT* NOT the slave 
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

  test_comms.initAddress(); // private method, you dont get to call this
  test_comms.init();

  test_comms.Bot_sendData(test_in);
  Serial.println("Data sent from roomba"); // can we display the data sent and received
  delay(1000);
}


// hmmm, it seems like we are both sending and recieving on both at the same time
// i.e when the other is sending this is sending (in setup)
// rather instead of doing any sending or recieving in setup
// we can try having it be in a ping pong order
// where one side pings and the other pongs back
// what i mean by that is one side is sending first (lets say dock), and the 
// other side (roomba) is waiting until it receives something.
// After the data is sent, the dock would have switched to receive mode 
// Then the roomba would send data (after it received the data)
// and the dock would now do the opposite (wait for data then send again)

void loop()
{
  // test_out not declared
  test_comms.Bot_readData(test_out);
  Serial.println("Data received from dock");
  delay(1000);
}
