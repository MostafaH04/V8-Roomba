#define MOTOR_ROWS 1
#include "Onboard_Comms.hpp"
#include "RF_Comms.hpp"

//Transmitter - Transmits data from the dock to the roomba
dataIn_t test_out;
test_out.dock_state = 1;
test_out.cv_x_pos = 1.0;
test_out.cv_y_pos = 2.0;
test_out.cv_z_pos = 3.0;
test_out.dock_rx_address = "00001";

Rf_Comms test_comms_out(7, 8, true);
CommsOut comms;

//Master
void setup() {
    Serial.begin(9600);
    comms = CommsOut(SLAVE_ADDR);

    test_comms_out.initAddress();
    test_comms_out.init();

    test_comms_out.Dock_sendData(test_out);
    Serial.println("Data sent from dock");
    delay(1000);
}

void loop()
{
    test_comms_out.Dock_readData(test_in);
    Serial.println("Data received from roomba");
    delay(1000);
}