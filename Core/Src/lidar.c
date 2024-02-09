/*
 * lidar.cpp
 *
 *  Created on: Feb 7, 2024
 *      Author: mahus
 */

#include "lidar.h"
// TODO: add PWM driver
// TODO: add interface

UART_HandleTypeDef* g_lidar_uart;
Lidar_t g_lidar;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == g_lidar_uart)
	{
		// TODO: stop this from happening if LiDAR isn't initialized yet
		if (LIDAR_scan(&g_lidar))
		{
			// TODO: Determine what if LiDAR is indeed running
		}
	}
}

bool LIDAR_init(UART_HandleTypeDef* huart)
{
	if (g_lidar.initialized) return false;

	g_lidar.huart = huart;
	g_lidar.scanning = false;
	g_lidar.point_cloud_new = false;

	g_lidar_uart = huart;

	g_lidar.initialized = true;

	return true;
}

bool LIDAR_scan(Lidar_t* lidar)
{
	if (!lidar->scanning)
		return false;

	if (lidar->point_cloud_new)
	{
		HAL_UART_Receive_DMA(
			lidar->huart,
			lidar->data_frame.samples_buffer,
			512
		);

		lidar->point_cloud_new = false;
		return true;
	}

	lidar->point_cloud_new = true;

	uint8_t scan_header[10];
	HAL_UART_Receive_DMA(
		lidar->huart,
		scan_header,
		10
	);

	// TODO: Parse scan header

	return true;
}

void LIDAR_start_scan(Lidar_t* lidar)
{
	// TODO: make this thread safe
	if (lidar->scanning)
		return;

	uint8_t scan_cmd[] = {LIDAR_START,  LIDAR_START_SCAN_CMD};
	HAL_UART_Transmit(
		lidar->huart,
		scan_cmd,
		2,
		10
	);

	lidar->scanning = true;
	lidar->point_cloud_new = false;

	// Read scan feedback
	uint8_t lidarRxFrame[7];

	HAL_UART_Receive_DMA(
		lidar->huart,
		lidarRxFrame,
		7
	);
}

void LIDAR_stop(Lidar_t* lidar)
{
	if (!lidar->scanning)
		return;

	uint8_t stop_cmd[] = {LIDAR_START, LIDAR_STOP_SCAN_CMD};
	HAL_UART_Transmit(
		lidar->huart,
		stop_cmd,
		sizeof(stop_cmd),
		10
	);
}

void LIDAR_info(Lidar_t* lidar)
{
	bool wasScanning = false;
	if (lidar->scanning)
	{
		wasScanning = true;
		LIDAR_stop(lidar);
	}

	uint8_t info_cmd[] = {LIDAR_START, LIDAR_GET_INFO_CMD};
	HAL_UART_Transmit(
		lidar->huart,
		info_cmd,
		sizeof(info_cmd),
		10
	);

	uint8_t info_buffer[20];
	HAL_UART_Receive(
		lidar->huart,
		info_buffer,
		20,
		10
	);

	// TODO: parse LiDAR info into lidar->info

	if (wasScanning)
	{
		LIDAR_start_scan(lidar);
	}
}

void LIDAR_health(Lidar_t* lidar)
{
	bool wasScanning = false;
	if (lidar->scanning)
	{
		wasScanning = true;
		LIDAR_stop(lidar);
	}

	uint8_t health_cmd[] = {LIDAR_START, LIDAR_GET_HEALTH_CMD};
	HAL_UART_Transmit(
		lidar->huart,
		health_cmd,
		sizeof(health_cmd),
		10
	);

	uint8_t info_buffer[3];
	HAL_UART_Receive(
		lidar->huart,
		info_buffer,
		3,
		10
	);

	// TODO: parse LiDAR info into lidar->info

	if (wasScanning)
	{
		LIDAR_start_scan(lidar);
	}
}

void LIDAR_reboot(Lidar_t* lidar)
{
	uint8_t reboot_cmd[] = {LIDAR_START, LIDAR_SOFT_RESTART_CMD};
	HAL_UART_Transmit(
		lidar->huart,
		reboot_cmd,
		sizeof(reboot_cmd),
		10
	);

	lidar->scanning = false;
	lidar->point_cloud_new = false;
}

// TODO: implement standby and motor speed fncs after adding pwm and pin interfaces


static void angle_analysis()
{

}

static void distance_analysis()
{

}

static bool check_parsing()
{

}
