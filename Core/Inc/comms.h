/*
 * comms.h
 *
 *  Created on: Feb 13, 2024
 *      Author: mahus
 */

#ifndef COMMS_H
#define COMMS_H

#include "usart.h"
#include "imu.h"
#include "motor_control.h"
#include "string.h"

#define RX_DATA_BUFFER_SIZE 25
#define TX_DATA_BUFFER_SIZE 28

typedef struct {
	float linear[3];
	float angular[3];
} Twist_Command_t;

// circular buffer for input data
typedef struct {
	unsigned char in_data[RX_DATA_BUFFER_SIZE];
	Twist_Command_t twist;

} Incoming_Data_t;

typedef struct {
	unsigned char out_data[TX_DATA_BUFFER_SIZE];
	IMU_Data_t* imuData;
} Sensor_Data_t;

typedef struct {
	UART_HandleTypeDef* uart;

	Incoming_Data_t incoming_data;
	Sensor_Data_t outgoing_sensor_data;
} Comms_t;

static Comms_t comms;
extern unsigned char* rx_data_buffer;
extern unsigned char* tx_data_buffer;

void Init_comms(UART_HandleTypeDef* huart, IMU_Data_t* imuData);
void parse_command(void);
void process_sensor_data(void);


#endif /* COMMS_H */
