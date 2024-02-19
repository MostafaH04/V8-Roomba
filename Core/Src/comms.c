/*
 * comms.c
 *
 *  Created on: Feb 14, 2024
 *      Author: mahus
 */

#include "comms.h"

Comms_t comms;
unsigned char* rx_data_buffer = comms.incoming_data.in_data;
unsigned char* tx_data_buffer = comms.outgoing_sensor_data.out_data;


// TODO: Make this thread safe

void Init_comms(UART_HandleTypeDef* huart)
{
	for (uint8_t i = 0; i < 3; i++)
	{
		comms.incoming_data.twist.linear[i] = 0;
		comms.incoming_data.twist.angular[i] = 0;
	}
	comms.uart = huart;
	HAL_UART_Receive_DMA(comms.uart, rx_data_buffer, RX_DATA_BUFFER_SIZE);
}

void parse_command(void)
{
	float* linear  = comms.incoming_data.twist.linear;
	float* angular = comms.incoming_data.twist.angular;

	unsigned char* buffer = comms.incoming_data.in_data;
	unsigned char buffer_temp[RX_DATA_BUFFER_SIZE-1];

	bool found_start = false;
	uint8_t start = 0;
	for (uint8_t i = 0; i < RX_DATA_BUFFER_SIZE; i++)
	{
		if (found_start)
		{
			buffer_temp[i] = buffer[start%RX_DATA_BUFFER_SIZE];
			start ++;
		}
		else if (buffer[i] == 0xFF)
		{
			start = i + 1;
			i = -1;
			found_start = true;
		}
	}

	if (!found_start) return;

	for (uint8_t i = 0; i < 3; i++)
	{
		memcpy(&linear[i], &buffer_temp[sizeof(float)*i], sizeof(float));
		memcpy(&angular[i], &buffer_temp[sizeof(float)*(3+i)], sizeof(float));
	}
}

void process_sensor_data(IMU_Data_t* imuData_1, IMU_Data_t* imuData_2)
{
	comms.outgoing_sensor_data.imuData_1 = imuData_1;

	float imu_data[7];
	unsigned char* buffer = comms.outgoing_sensor_data.out_data;
	buffer[0] = 0xFF;

	imu_data[0] = comms.outgoing_sensor_data.imuData_1->accX;
	imu_data[1] = comms.outgoing_sensor_data.imuData_1->accY;
	imu_data[2] = comms.outgoing_sensor_data.imuData_1->accZ;
	imu_data[3] = comms.outgoing_sensor_data.imuData_1->gyroX;
	imu_data[4] = comms.outgoing_sensor_data.imuData_1->gyroY;
	imu_data[5] = comms.outgoing_sensor_data.imuData_1->gyroZ;
	imu_data[6] = comms.outgoing_sensor_data.imuData_1->temp;

	for (uint8_t i = 0; i < 8; i++)
	{
		memcpy(&buffer[i*sizeof(float)+1], &imu_data[i], sizeof(float));
	}

	comms.outgoing_sensor_data.imuData_2 = imuData_2;

	imu_data[0] = comms.outgoing_sensor_data.imuData_2->accX;
	imu_data[1] = comms.outgoing_sensor_data.imuData_2->accY;
	imu_data[2] = comms.outgoing_sensor_data.imuData_2->accZ;
	imu_data[3] = comms.outgoing_sensor_data.imuData_2->gyroX;
	imu_data[4] = comms.outgoing_sensor_data.imuData_2->gyroY;
	imu_data[5] = comms.outgoing_sensor_data.imuData_2->gyroZ;
	imu_data[6] = comms.outgoing_sensor_data.imuData_2->temp;

	for (uint8_t i = 0; i < 8; i++)
	{
		memcpy(&buffer[i*sizeof(float)+29], &imu_data[i], sizeof(float));
	}
}


