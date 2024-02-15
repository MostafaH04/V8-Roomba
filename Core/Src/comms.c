/*
 * comms.c
 *
 *  Created on: Feb 14, 2024
 *      Author: mahus
 */

#include "comms.h"

static Comms_t comms;
unsigned char* rx_data_buffer = comms.incoming_data.in_data;
unsigned char* tx_data_buffer = comms.outgoing_sensor_data.out_data;


// TODO: Make this thread safe

void Init_comms(UART_HandleTypeDef* huart, IMU_Data_t* imuData)
{
	comms.uart = huart;
	comms.outgoing_sensor_data.imuData = imuData;
}

void parse_command(void)
{
	float* linear  = comms.incoming_data.twist.linear;
	float* angular = comms.incoming_data.twist.angular;

	unsigned char* buffer = comms.incoming_data.in_data;

	for (uint8_t i = 0; i < 3; i++)
	{
		memcpy(&linear[i], &buffer[sizeof(float)*i], sizeof(float));
		memcpy(&angular[i], &buffer[sizeof(float)*(3+i)], sizeof(float));
	}
}

void process_sensor_data(void)
{
	float imu_data[7];
	unsigned char* buffer = comms.outgoing_sensor_data.out_data;

	imu_data[0] = comms.outgoing_sensor_data.imuData->accX;
	imu_data[1] = comms.outgoing_sensor_data.imuData->accY;
	imu_data[2] = comms.outgoing_sensor_data.imuData->accZ;
	imu_data[3] = comms.outgoing_sensor_data.imuData->gyroX;
	imu_data[4] = comms.outgoing_sensor_data.imuData->gyroY;
	imu_data[5] = comms.outgoing_sensor_data.imuData->gyroZ;
	imu_data[6] = comms.outgoing_sensor_data.imuData->temp;

	for (uint8_t i = 0; i < 8; i++)
	{
		memcpy(&buffer[i*sizeof(float)], &imu_data[i], sizeof(float));
	}
}


