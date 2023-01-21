#ifndef RF_COMMS_H
#define RF_COMMS_H

#include "Arduino.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "Onboard_Comms.hpp"

#define BOT_TX "00001"
#define BOT_RX "00002"


//Roomba to dock
typedef struct{
    //US sensor readings
    float US_reading_1;
    float US_reading_2;
    
    //mpu6050 - gyroscope position readings
    float x_pos;
    float y_pos;
    float z_pos;

    //current roomba state
    int roomba_state;
    
    //NRF24L01 - RF comms transeiver info (5-bit address): Roomba is receiving
    const uint8_t roomba_tx_address[5];

} dataOut_t;


//Dock to roomba
typedef struct{
    int dock_state;

    //CV position readings (if we plan to have a camera on the dock)
    float cv_x_pos;
    float cv_y_pos;
    float cv_z_pos;
    
    // *EDIT* if the dock is controlling, should also send speed
    float movementSpeed; 

    //NRF24L01 - RF comms transeiver info (5-bit address): Dock is transmitting
    const uint8_t dock_rx_address[5];

} dataIn_t;

class Rf_Comms
{
    private:
        int chipEnable;
        int chipSelect;
        
        byte addresses[][6];
        bool dock;

        void initAddresses();

        RF24 radio;

    public:
        Rf_Comms();
        Rf_Comms(int CE, int CSN, bool dock_in);

        void init();

        void Dock_readData(dataOut_t &roombaData);
        void Dock_sendData(dataIn_t const &dataPackage);

        void Bot_readData(dataIn_t &dockData);
        void Bot_sendData(dataOut_t const &dataPackage);

};

#endif 
