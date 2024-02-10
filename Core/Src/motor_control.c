/*
 * motor_control.c
 *
 *  Created on: Feb 10, 2024
 *      Author: mahus
 */

#include "motor_control.h"

Motor_t MOTOR_init(
		TIM_HandleTypeDef* const timer_fw, uint32_t channel_fw,
		TIM_HandleTypeDef* const timer_bw, uint32_t channel_bw,
		float radius
	)
{
	Motor_t ret;
	ret.channel_fw = channel_fw;
	ret.timer_fw = timer_fw;

	ret.channel_bw = channel_bw;
	ret.timer_bw = timer_bw;

	ret.wheel_radius = radius;
	ret.speed = 0;

	HAL_TIM_PWM_Start(timer_fw, channel_fw);
	HAL_TIM_PWM_Start(timer_bw, channel_bw);

	return ret;
}

void MOTOR_drive(Motor_t* motor)
{
	// TODO: make this thread safe
	if (motor->speed >= 0)
	{
		__HAL_TIM_SetCompare(motor->timer_fw, motor->channel_fw, motor->speed * AUTO_RELOAD_REG);
		__HAL_TIM_SetCompare(motor->timer_bw, motor->channel_bw, 0);
	}
	else
	{
		__HAL_TIM_SetCompare(motor->timer_bw, motor->channel_bw, (-motor->speed) * AUTO_RELOAD_REG);
		__HAL_TIM_SetCompare(motor->timer_fw, motor->channel_fw, 0);
	}
}

void MOTOR_set_speed(Motor_t* motor, float speed)
{
	// TODO: make this thread safe
	if (speed > 1)
		speed = 1;
	else if (speed < -1)
		speed = -1;
	motor->speed = speed;
}

Chassis_Controller_t CHASSIS_init(
		Motor_t* left_front,
		Motor_t* left_back,
		Motor_t* right_front,
		Motor_t* right_back,
		float wheel_base
	)
{
	Chassis_Controller_t ret;
	ret.motors[0] = left_front;
	ret.motors[1] = left_back;
	ret.motors[2] = right_front;
	ret.motors[3] = right_back;

	ret.wheel_base = wheel_base;

	return ret;
}

void CHASSIS_set_speed(
		Chassis_Controller_t* chassis,
		float speed,
		float omega
	)
{
	for (uint8_t i = 0; i < 4; i++)
	{
		float motor_speed;
		motor_speed = calculate_wheel_rot(
				speed,
				omega,
				chassis->motors[i]->wheel_radius,
				chassis->wheel_base,
				i/2
			);

		MOTOR_set_speed(chassis->motors[i], motor_speed);
	}
}

void CHASSIS_drive(Chassis_Controller_t* chassis)
{
	for (uint8_t i = 0; i < 4; i++)
	{
		MOTOR_drive(chassis->motors[i]);
	}
}

static float calculate_wheel_rot(
		float speed,
		float omega,
		float radius,
		float wheel_base,
		uint8_t right
	)
{
	float ret = speed / radius + (right?-1:1) *
			wheel_base / 2 * omega / radius;

	return ret/MAX_WHEEL_SPEED;
}

