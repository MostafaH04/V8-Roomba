/*
 * lidar.cpp
 *
 *  Created on: Feb 7, 2024
 *      Author: mahus
 */

#include "lidar.h"

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

void LIDAR_init(UART_HandleTypeDef* huart)
{
	g_lidar.huart = huart;
	g_lidar.scanning = false;
	g_lidar.point_cloud_new = false;

	g_lidar_uart = huart;
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

