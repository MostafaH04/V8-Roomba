/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor_control.h"
#include "imu.h"
#include "comms.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
Motor_t motor1, motor2, motor3, motor4;
Chassis_Controller_t chassis;
IMU_t imu_1, imu_2;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t driveTaskHandle;
const osThreadAttr_t driveTask_attributes = {
  .name = "driveTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t commsTaskHandle;
const osThreadAttr_t commsTask_attributes = {
  .name = "commsTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t imuTaskHandle;
const osThreadAttr_t imuTask_attributes = {
  .name = "imuTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

osMutexId_t incomingDataMutex;
const osMutexAttr_t incomingDataMutex_attr = {
  .name = "incomingDataMutex",
  .attr_bits = osMutexPrioInherit,
  .cb_mem = NULL,
  .cb_size = 0U
};

osMutexId_t imuDataMutex;
const osMutexAttr_t imuDataMutex_attr = {
  .name = "imuDataMutex",
  .attr_bits = osMutexPrioInherit,
  .cb_mem = NULL,
  .cb_size = 0U
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void StartDriveTask(void *arg);
void StartCommsTask(void *arg);
void StartImuTask(void *arg);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	/* Initialize Chassis Controller */
	motor1 = MOTOR_init(&htim1, TIM_CHANNEL_1, &htim1, TIM_CHANNEL_2,
		WHEEL_RAD);
	motor2 = MOTOR_init(&htim1, TIM_CHANNEL_3, &htim1, TIM_CHANNEL_4,
		WHEEL_RAD);
	motor3 = MOTOR_init(&htim3, TIM_CHANNEL_1, &htim3, TIM_CHANNEL_2,
		WHEEL_RAD);
	motor4 = MOTOR_init(&htim3, TIM_CHANNEL_3, &htim3, TIM_CHANNEL_4,
		WHEEL_RAD);

	chassis = CHASSIS_init(&motor1, &motor2, &motor3,
		&motor4, 0.25);

	imu_2 = IMU_Init(
		true, &hi2c1,
		GPIOB,
		GPIO_PIN_15);

	imu_1 = IMU_Init(
		false, &hi2c1,
		GPIOB,
		GPIO_PIN_14);

	Init_comms(&huart2);

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  incomingDataMutex = osMutexNew(&incomingDataMutex_attr);
  imuDataMutex = osMutexNew(&imuDataMutex_attr);

  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
  driveTaskHandle = osThreadNew(StartDriveTask, NULL, &driveTask_attributes);
  commsTaskHandle = osThreadNew(StartCommsTask, NULL, &commsTask_attributes);
  imuTaskHandle = osThreadNew(StartImuTask, NULL, &imuTask_attributes);
  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	CHASSIS_drive(&chassis);
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

void StartDriveTask(void *arg)
{
  osStatus_t mutex_status;
  while(1)
  {
	if (incomingDataMutex != NULL)
	{
      mutex_status = osMutexAcquire(incomingDataMutex, osWaitForever);
      if (mutex_status == osOK){
    	  float omega = comms.incoming_data.twist.angular[2];
		  float speed = comms.incoming_data.twist.linear[0];
		  CHASSIS_set_speed(&chassis, speed, omega);
      }
      osMutexRelease(incomingDataMutex);
	}
    CHASSIS_drive(&chassis);
    osDelay(1);
  }
}

void StartCommsTask(void *arg)
{
  osStatus_t mutex_status;
  while(1)
  {
	if (imuDataMutex != NULL)
	{
	  mutex_status = osMutexAcquire(imuDataMutex, 0);
	  if (mutex_status == osOK){
	    process_sensor_data(&(imu_1.imuData), &(imu_2.imuData));

	    osMutexRelease(imuDataMutex);
	    int32_t state = osKernelLock();
	    HAL_UART_Transmit(comms.uart, tx_data_buffer, TX_DATA_BUFFER_SIZE,
		    1000);
	    osKernelUnlock();
	  }
	}
	osDelay(1);
  }
}

void StartImuTask(void *arg)
{
  osStatus_t mutex_status;
  while(1)
  {
	if (imuDataMutex != NULL)
	{
	  mutex_status = osMutexAcquire(imuDataMutex, osWaitForever);
	  if (mutex_status == osOK){
		  IMU_updateData(&imu_1);
		  IMU_updateData(&imu_2);
	  }
	  osMutexRelease(imuDataMutex);
	}
	osDelay(1000/IMU_REFRESH_FREQ);
  }
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

