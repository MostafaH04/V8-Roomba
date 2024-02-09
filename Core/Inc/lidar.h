/*
 * lidar.h
 *
 *  Created on: Feb 7, 2024
 *      Author: mahus
 */

#ifndef LIDAR_H
#define LIDAR_H

#include <stdbool.h>
#include "stdint.h"
#include "usart.h"

#define LIDAR_START 0xA5

// Lidar System Commands
#define LIDAR_START_SCAN_CMD 0x60
#define LIDAR_STOP_SCAN_CMD 0x65
#define LIDAR_GET_INFO_CMD 0x90
#define LIDAR_GET_HEALTH_CMD 0x91
#define LIDAR_SOFT_RESTART_CMD 0x80

// Lidar response mode
#define LIDAR_SINGLE_RESPONSE 0x0
#define LIDAR_CNTS_RESPONSE 0x1

extern UART_HandleTypeDef* g_lidar_uart;

//
typedef struct{
	uint8_t start[2];
	uint8_t length[4];
	uint8_t mode[1];
	uint8_t type_code[1];
	uint8_t samples_buffer[512];
} Lidar_Data_Frame_t;

typedef struct{
	UART_HandleTypeDef* huart;
	Lidar_Data_Frame_t data_frame;
	bool scanning;
	bool point_cloud_new;
} Lidar_t;

extern Lidar_t g_lidar;

static void angle_analysis();
static void distance_analysis();
static bool check_parsing();

static void read_scan();

void LIDAR_init(UART_HandleTypeDef* huart);

bool LIDAR_scan(Lidar_t* lidar);

void LIDAR_start_scan(Lidar_t* lidar);

void LIDAR_stop();

void LIDAR_info();

void LIDAR_health();

void LIDAR_reboot();

void LIDAR_standby();

void LIDAR_motor_speed(float speed);

#endif /* LIDAR_H */
