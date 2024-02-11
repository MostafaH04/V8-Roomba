/*
 * imu.h
 *
 *  Created on: Feb 11, 2024
 *      Author: mahus
 */

#ifndef IMU_H
#define IMU_H

#include "i2c.h"
#include "stdbool.h"
#include "math.h"
#include "main.h"

#define ADDRESS_LOW 0x68
#define ADDRESS_HIGH 0x69

#define SELF_TEST_X 0x0D
#define SELF_TEST_Y 0x0E
#define SELF_TEST_Z 0x0F
#define SELF_TEST_A 0x10
#define SMPLRT_DIV 0x19
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define MOT_THR 0x1F
#define FIFO_EN 0x23
#define I2C_MST_CTRL 0x24
#define I2C_SLV0_ADDR 0x25
#define I2C_SLV0_REG 0x26
#define I2C_SLV0_CTRL 0x27
#define I2C_SLV1_ADDR 0x28
#define I2C_SLV1_REG 0x29
#define I2C_SLV1_CTRL 0x2A
#define I2C_SLV2_ADDR 0x2B
#define I2C_SLV2_REG 0x2C
#define I2C_SLV2_CTRL 0x2D
#define I2C_SLV3_ADDR 0x2E
#define I2C_SLV3_REG 0x2F
#define I2C_SLV3_CTRL 0x30
#define I2C_SLV4_ADDR 0x31
#define I2C_SLV4_REG 0x32
#define I2C_SLV4_DO 0x33
#define I2C_SLV4_CTRL 0x34
#define I2C_SLV4_DI 0x35
#define I2C_MST_STATUS 0x36
#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38
#define INT_STATUS 0x3A
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48
#define EXT_SENS_DATA_00 0x49
#define EXT_SENS_DATA_01 0x4A
#define EXT_SENS_DATA_02 0x4B
#define EXT_SENS_DATA_03 0x4C
#define EXT_SENS_DATA_04 0x4D
#define EXT_SENS_DATA_05 0x4E
#define EXT_SENS_DATA_06 0x4F
#define EXT_SENS_DATA_07 0x50
#define EXT_SENS_DATA_08 0x51
#define EXT_SENS_DATA_09 0x52
#define EXT_SENS_DATA_10 0x53
#define EXT_SENS_DATA_11 0x54
#define EXT_SENS_DATA_12 0x55
#define EXT_SENS_DATA_13 0x56
#define EXT_SENS_DATA_14 0x57
#define EXT_SENS_DATA_15 0x58
#define EXT_SENS_DATA_16 0x59
#define EXT_SENS_DATA_17 0x5A
#define EXT_SENS_DATA_18 0x5B
#define EXT_SENS_DATA_19 0x5C
#define EXT_SENS_DATA_20 0x5D
#define EXT_SENS_DATA_21 0x5E
#define EXT_SENS_DATA_22 0x5F
#define EXT_SENS_DATA_23 0x60
#define I2C_SLV0_DO 0x63
#define I2C_SLV1_DO 0x64
#define I2C_SLV2_DO 0x65
#define I2C_SLV3_DO 0x66
#define I2C_MST_DELAY_CT_RL 0x67
#define SIGNAL_PATH_RESET 0x68
#define MOT_DETECT_CTRL 0x69
#define USER_CTRL 0x6A
#define PWR_MGMT_1 0x6B
#define PWR_MGMT_2 0x6C
#define FIFO_COUNTH 0x72
#define FIFO_COUNTL 0x73
#define FIFO_R_W 0x74
#define WHO_AM_I 0x75

#define REG_RESET 0x00
#define REG_107_RESET 0x40
#define REG_117_RESET 0x68

#define GYRO_FS_250_RANGE 131
#define GYRO_FS_500_RANGE 65.5
#define GYRO_FS_1000_RANGE 32.8
#define GYRO_FS_2000_RANGE 16.4

#define ACCEL_FS_2_RANGE 16384
#define ACCEL_FS_4_RANGE 8192
#define ACCEL_FS_8_RANGE 4096
#define ACCEL_FS_16_RANGE 2048

#define GYRO_OUTPUT_RATE_HZ 8000


typedef struct{
	float accX, accY, accZ;
	float gyroX, gyroY, gyroZ;
	float temp;
} IMU_Data_t;

typedef enum {
	ACCEL_FULLSCALE_2 = 0x00,
	ACCEL_FULLSCALE_4 = 0x01,
	ACCEL_FULLSCALE_8 = 0x02,
	ACCEL_FULLSCALE_16 = 0x03
} Accel_FullScale;

typedef enum  {
	GYRO_FULLSCALE_250 = 0x00,
	GYRO_FULLSCALE_500 = 0x01,
	GYRO_FULLSCALE_1000 = 0x02,
	GYRO_FULLSCALE_2000 = 0x03
} Gyro_FullScale;

typedef enum  {
    TEMP_FIFO_EN = 0x80,
    XG_FIFO_EN = 0x40,
    YG_FIFO_EN = 0x20,
    ZG_FIFO_EN = 0x10,
    ACCEL_FIFO_EN = 0x08,
    SLV2_FIFO_EN = 0x04,
    SLV1_FIFO_EN = 0x02,
    SLV0_FIFO_EN = 0x01,
    SLV3_FIFO_EN = 0x100
} Fifo_Config;

typedef enum  {
    MULT_MST_EN = 0x80,
    WAIT_FOR_ES = 0x40,
    SLV_3_FIFO_EN = 0x20,
    I2C_MST_P_NSR = 0x10,
} Master_Control_Config;

typedef enum  {
    SLAVE_0,
    SLAVE_1,
    SLAVE_2,
    SLAVE_3,
    SLAVE_4
} Slave;

typedef enum  {
    INTERNAL_8MHZ = 0x00,
    PLL_X_GYRO = 0x01,
    PLL_Y_GYRO = 0x02,
    PLL_Z_GYRO = 0x03,
    PLL_EXT_33_KHZ = 0x04,
    PLL_EXT_19_MHZ= 0x05,
    RESET_CLK = 0x07
} Clock_Select;

typedef enum  {
    Freq_1_25Hz = 0x00,
    Freq_5Hz = 0x01,
    Freq_20Hz = 0x02,
    Freq_40Hz = 0x03
} Wake_Up_Frequency;

#define INIT_FAIL 0
#define INIT_SUCCESS 1

typedef struct {
	uint16_t address;

	float accErrorX, accErrorY;
	float gyroErrorX, gyroErrorY, gyroErrorZ;
	float LSB_g;
	float LSB_deg_s;

	float calibAx, calibAy, calibAz;
	float calibGx, calibGy, calibGz;

	GPIO_TypeDef* addressPin;
	uint16_t addressPinVal;

	IMU_Data_t imuData;

	I2C_HandleTypeDef* i2c;
} IMU_t;

IMU_t IMU_Init(
	bool setAddressHigh,
	I2C_HandleTypeDef* hi2c,
	GPIO_TypeDef* addressPinReg,
	uint16_t addressPin
);

bool selfTest(IMU_t* imu);
void setSampleRate(IMU_t* imu, uint16_t sample_rate_khz);
void setFullScaleGyro(IMU_t* imu, Gyro_FullScale gyro_fs_setting);
void setFullScaleAccel(IMU_t* imu, Accel_FullScale accel_fs_setting);
void readAccelRegisters(IMU_t* imu);
void readGyroRegisters(IMU_t* imu);
void readTempRegisters(IMU_t* imu);
void updateData(IMU_t* imu);
void resetRegisters(IMU_t* imu);
void sleepMode(IMU_t* imu, bool sleep);
void selectClockSource(IMU_t* imu, Clock_Select clock_sel);
void disableTemp(IMU_t* imu, bool disable);
void sleepCycle(IMU_t* imu, Wake_Up_Frequency cycleFreq);

#endif /* IMU_H */
