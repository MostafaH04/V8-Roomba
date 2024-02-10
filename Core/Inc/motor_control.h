/*
 * motor_control.h
 *
 *  Created on: Feb 10, 2024
 *      Author: mahus
 */

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "tim.h"

#define AUTO_RELOAD_REG 839

/* Motor */
typedef struct {
	TIM_HandleTypeDef* timer_fw;
	uint32_t channel_fw;

	TIM_HandleTypeDef* timer_bw;
	uint32_t channel_bw;

	float speed;
	float wheel_radius;
} Motor_t;

Motor_t MOTOR_init(
		TIM_HandleTypeDef* const timer_fw, uint32_t channel_fw,
		TIM_HandleTypeDef* const timer_bw, uint32_t channel_bw,
		float radius
);

void MOTOR_drive(Motor_t* motor);
void MOTOR_set_speed(Motor_t* motor, float speed);


/* Chassis Controller */

typedef struct {
	Motor_t *motors[4];
	float wheel_base;
} Chassis_Controller_t;


Chassis_Controller_t CHASSIS_init(
		Motor_t* left_front,
		Motor_t* left_back,
		Motor_t* right_front,
		Motor_t* right_back,
		float wheel_base
);

void CHASSIS_set_speed(
		Chassis_Controller_t* chassis,
		float speed,
		float omega
);

void CHASSIS_drive(Chassis_Controller_t* chassis);

static float calculate_wheel_rot(
		float speed,
		float omega,
		float radius,
		float wheel_base,
		uint8_t right
);


#endif /* INC_MOTOR_CONTROL_H_ */
