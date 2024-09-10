/*
 * imu.c
 *
 *  Created on: Feb 11, 2024
 *      Author: mahus
 */

#include "imu.h"
#include "cmsis_os.h"

static void calibrate_imu(IMU_t* imu);
static void correct_data(IMU_t* imu);
static void startPins(IMU_t* imu);
static bool initialize(IMU_t* imu);
static double factoryTrimGyro(uint8_t testVal);
static double factoryTrimAccel(uint8_t testVal);

IMU_t IMU_Init(
	bool setAddressHigh,
	I2C_HandleTypeDef* hi2c,
	GPIO_TypeDef* addressPinReg,
	uint16_t addressPin
)
{
	IMU_t ret;

	ret.addressPin = addressPinReg;
	ret.addressPinVal = addressPin;

	if (setAddressHigh)
	{
		ret.address = ADDRESS_HIGH;
	}
	else
	{
		ret.address = ADDRESS_LOW;
	}

	startPins(&ret);

	ret.i2c = hi2c;

	initialize(&ret);

	return ret;
}

bool IMU_selfTest(IMU_t* imu)
{
	uint8_t test_recv[4];

	float GyroXDisabled, GyroYDisabled, GyroZDisabled;
	float AccelXDisabled, AccelYDisabled, AccelZDisabled;

	uint8_t normalMeas[1] = {0b00011000};
	HAL_I2C_Mem_Write(imu->i2c, (imu->address<<1), GYRO_CONFIG, 1,
			normalMeas, 1, HAL_MAX_DELAY);

	IMU_readAccelRegisters(imu);
	IMU_readGyroRegisters(imu);

	GyroXDisabled = imu->imuData.gyroX;
	GyroYDisabled = imu->imuData.gyroY;
	GyroZDisabled = imu->imuData.gyroZ;

	AccelXDisabled = imu->imuData.accX;
	AccelYDisabled = imu->imuData.accY;
	AccelZDisabled = imu->imuData.accZ;

	float StrGyroX, StrGyroY, StrGyroZ;
	float StrAccelX, StrAccelY, StrAccelZ;

	uint8_t selfTest = 0xF8; //0b11111000
	HAL_I2C_Mem_Write(imu->i2c, (imu->address<<1), GYRO_CONFIG, 1,
			&selfTest, sizeof(selfTest), HAL_MAX_DELAY);

	IMU_readAccelRegisters(imu);
	IMU_readGyroRegisters(imu);

	StrGyroX = imu->imuData.gyroX - GyroXDisabled;
	StrGyroY = imu->imuData.gyroY - GyroYDisabled;
	StrGyroZ = imu->imuData.gyroZ - GyroZDisabled;

	StrAccelX = imu->imuData.accX - AccelXDisabled;
	StrAccelY = imu->imuData.accY - AccelYDisabled;
	StrAccelZ = imu->imuData.accZ - AccelZDisabled;

	HAL_I2C_Mem_Write(imu->i2c, (imu->address<<1), GYRO_CONFIG, 1,
			normalMeas, sizeof(normalMeas), HAL_MAX_DELAY);

	HAL_I2C_Mem_Read(imu->i2c, (imu->address<<1) | 0x01, SELF_TEST_X, 1,
	test_recv, 4, HAL_MAX_DELAY);

	uint8_t test_a_x, test_a_y, test_a_z;
	uint8_t test_g_x, test_g_y, test_g_z;

	test_a_x = (test_recv[0] & 0b11100000) >> 1
			| ((test_recv[3] & 0b00110000) << 4);
	test_a_y = (test_recv[1] & 0b11100000) >> 1
			| ((test_recv[3] & 0b00001100) << 2);
	test_a_z = (test_recv[2] & 0b11100000) >> 1
			| ((test_recv[3] & 0b00000011));

	test_g_x = (test_recv[0] & 0b00011111);
	test_g_y = (test_recv[1] & 0b00011111);
	test_g_z = (test_recv[2] & 0b00011111);

	float factTrimGx = 0, factTrimGy = 0, factTrimGz = 0;
	float factTrimAx = 0, factTrimAy = 0, factTrimAz = 0;

	if (test_g_x != 0)
		factTrimGx = factoryTrimGyro(test_g_x);
	if (test_g_y != 0)
		factTrimGy = factoryTrimGyro(test_g_y);
	if (test_g_z != 0)
		factTrimGz = factoryTrimGyro(test_g_z);

	if (test_a_x != 0)
		factTrimAx = factoryTrimAccel(test_a_x);
	if (test_a_y != 0)
		factTrimAy = factoryTrimAccel(test_a_y);
	if (test_a_z != 0)
		factTrimAz = factoryTrimAccel(test_a_z);

	float accXRes = (StrAccelX - factTrimAx)/factTrimAx * 100;
	float accYRes = (StrAccelY - factTrimAy)/factTrimAy * 100;
	float accZRes = (StrAccelZ - factTrimAz)/factTrimAz * 100;

	float gyroXRes = (StrGyroX - factTrimGx)/factTrimGx * 100;
	float gyroYRes = (StrGyroY - factTrimGy)/factTrimGy * 100;
	float gyroZRes = (StrGyroZ - factTrimGz)/factTrimGz * 100;

	bool passAccX = fabs(accXRes) < 14;
	bool passAccY = fabs(accYRes) < 14;
	bool passAccZ = fabs(accZRes) < 14;

	bool passGyroX = fabs(gyroXRes) < 14;
	bool passGyroY = fabs(gyroYRes) < 14;
	bool passGyroZ = fabs(gyroZRes) < 14;

	return passAccX && passAccY && passAccZ && passGyroX
			&& passGyroY && passGyroZ;
}

void IMU_setSampleRate(IMU_t* imu, uint16_t sample_rate_khz)
{
	uint8_t rate_divider = (uint8_t)((GYRO_OUTPUT_RATE_HZ / sample_rate_khz) - 1);
	HAL_I2C_Mem_Write(imu->i2c, (imu->address<<1), SMPLRT_DIV, 1,
			&rate_divider, 1, HAL_MAX_DELAY);
}

void IMU_setFullScaleGyro(IMU_t* imu, Gyro_FullScale gyro_fs_setting)
{
	uint8_t config = (uint8_t)(gyro_fs_setting << 3);
	HAL_I2C_Mem_Write(imu->i2c, (imu->address<<1), GYRO_CONFIG, 1,
			&config, 1, HAL_MAX_DELAY);

	switch(gyro_fs_setting)
	{
		case 0x00: // 250
			imu->LSB_deg_s = GYRO_FS_250_RANGE;
			break;
		case 0x01: //500
			imu->LSB_deg_s = GYRO_FS_500_RANGE;
			break;
		case 0x02: // 1000
			imu->LSB_deg_s = GYRO_FS_1000_RANGE;
		  break;
		case 0x03: // 2000
			imu->LSB_deg_s = GYRO_FS_2000_RANGE;
			break;
	}
}

void IMU_setFullScaleAccel(IMU_t* imu, Accel_FullScale accel_fs_setting)
{
	uint8_t config = (uint8_t)(accel_fs_setting << 3);
	HAL_I2C_Mem_Write(imu->i2c, (imu->address<<1), ACCEL_CONFIG, 1,
			&config, 1, HAL_MAX_DELAY);

	switch(accel_fs_setting)
	{
		case 0x00: // 2
			imu->LSB_g = ACCEL_FS_2_RANGE;
			break;
		case 0x01: // 4
			imu->LSB_g = ACCEL_FS_4_RANGE;
			break;
		case 0x02: // 8
			imu->LSB_g = ACCEL_FS_8_RANGE;
			break;
		case 0x03: // 16
			imu->LSB_g = ACCEL_FS_16_RANGE;
			break;
	}
}

void IMU_readAccelRegisters(IMU_t* imu)
{
	int16_t accelX, accelY, accelZ;
	uint8_t accelRec[6];


	int32_t state = osKernelLock();
	HAL_I2C_Mem_Read(imu->i2c,(imu->address<<1) | 0x01, ACCEL_XOUT_H, 1,
			accelRec, 6, HAL_MAX_DELAY);
	osKernelUnlock();


	accelX = (int16_t)(accelRec[0] << 8 | accelRec[1]);
	accelY = (int16_t)(accelRec[2] << 8 | accelRec[3]);
	accelZ = (int16_t)(accelRec[4] << 8 | accelRec[5]);

	imu->imuData.accX = accelX;
	imu->imuData.accY = accelY;
	imu->imuData.accZ = accelZ;
}

void IMU_readGyroRegisters(IMU_t* imu)
{
	int16_t gyroX, gyroY, gyroZ;
	uint8_t gyroRec[6];


	int32_t state = osKernelLock();
	HAL_I2C_Mem_Read(imu->i2c,(imu->address<<1) | 0x01,GYRO_XOUT_H, 1,
			gyroRec, 6, HAL_MAX_DELAY);
	osKernelUnlock();


	gyroX = (int16_t)(gyroRec[0] << 8 | gyroRec[1]);
	gyroY = (int16_t)(gyroRec[2] << 8 | gyroRec[3]);
	gyroZ = (int16_t)(gyroRec[4] << 8 | gyroRec[5]);

	imu->imuData.gyroX = gyroX;
	imu->imuData.gyroY = gyroY;
	imu->imuData.gyroZ = gyroZ;
}

void IMU_readTempRegisters(IMU_t* imu)
{
	int16_t temp;
	uint8_t tempRecv[2];

	int32_t state = osKernelLock();

	HAL_I2C_Mem_Read(imu->i2c, (imu->address<<1) | 0x01, TEMP_OUT_H, 1,
			tempRecv, 2, HAL_MAX_DELAY);
	osKernelUnlock();


	temp = (int16_t)(tempRecv[0] << 8 | tempRecv[1]);
	temp = temp / 340 + 36.53;

	imu->imuData.temp = temp;
}

void IMU_updateData(IMU_t* imu)
{
	IMU_readTempRegisters(imu);
	IMU_readGyroRegisters(imu);
	IMU_readAccelRegisters(imu);
	correct_data(imu);
}

void IMU_resetRegisters(IMU_t* imu)
{
	uint8_t resetRegisters = 0x07; // 0b00000111
	HAL_I2C_Mem_Write(imu->i2c, (imu->address<<1), SIGNAL_PATH_RESET, 1,
			&resetRegisters, 1, HAL_MAX_DELAY);
}

void IMU_sleepMode(IMU_t* imu, bool sleep)
{
	uint8_t pwr_mgmt = 0x00;
	HAL_I2C_Mem_Read(imu->i2c, (imu->address<<1) | 0x01, PWR_MGMT_1, 1,
			&pwr_mgmt, 1, HAL_MAX_DELAY);

	pwr_mgmt = (pwr_mgmt & 0b10111111) | ((sleep?0x01:0x00) << 6);

	HAL_I2C_Mem_Write(imu->i2c, (imu->address<<1), PWR_MGMT_1, 1,
			&pwr_mgmt, 1, HAL_MAX_DELAY);
}
void IMU_selectClockSource(IMU_t* imu, Clock_Select clock_sel)
{
	uint8_t pwr_mgmt = 0x00;
	HAL_I2C_Mem_Read(imu->i2c, (imu->address<<1) | 0x01, PWR_MGMT_1, 1,
			&pwr_mgmt, 1, HAL_MAX_DELAY);

	pwr_mgmt = (pwr_mgmt & 0b11111000) | clock_sel;

	HAL_I2C_Mem_Write(imu->i2c, (imu->address<<1), PWR_MGMT_1   , 1,
			&pwr_mgmt, 1, HAL_MAX_DELAY);
}

void IMU_disableTemp(IMU_t* imu, bool disable)
{
	uint8_t pwr_mgmt = 0x00;
	HAL_I2C_Mem_Read(imu->i2c, (imu->address<<1) | 0x01, PWR_MGMT_1, 1,
			&pwr_mgmt, 1, HAL_MAX_DELAY);

	pwr_mgmt = (pwr_mgmt & 0b11110111) | (disable?0x01:0x00) << 3;

	HAL_I2C_Mem_Write(imu->i2c, (imu->address<<1), PWR_MGMT_1, 1,
			&pwr_mgmt, 1, HAL_MAX_DELAY);
}

void IMU_sleepCycle(IMU_t* imu, Wake_Up_Frequency cycleFreq)
{
	uint8_t pwr_mgmt2 = (uint8_t)(cycleFreq << 6);
	HAL_I2C_Mem_Write(imu->i2c, (imu->address<<1), PWR_MGMT_2, 1,
			&pwr_mgmt2, 1, HAL_MAX_DELAY);
}

static void calibrate_imu(IMU_t* imu)
{
	float buffAx = 0, buffAy = 0, buffAz = 0;
	float buffGx = 0, buffGy = 0, buffGz = 0;
	const int TOTAL_MEASUREMENTS = 200;

	for (int measIter = 0; measIter < TOTAL_MEASUREMENTS; measIter ++)
	{
		IMU_readTempRegisters(imu);
		IMU_readGyroRegisters(imu);
		IMU_readAccelRegisters(imu);

		buffAx += imu->imuData.accX;
		buffAy += imu->imuData.accY;
		buffAz += imu->imuData.accZ + imu->LSB_g;

		buffGx += imu->imuData.gyroX;
		buffGy += imu->imuData.gyroY;
		buffGz += imu->imuData.gyroZ;
	}

	imu->calibAx = buffAx / TOTAL_MEASUREMENTS;
	imu->calibAy = buffAy / TOTAL_MEASUREMENTS;
	imu->calibAz = buffAz / TOTAL_MEASUREMENTS;

	imu->calibGx = buffGx / TOTAL_MEASUREMENTS;
	imu->calibGy = buffGy / TOTAL_MEASUREMENTS;
	imu->calibGz = buffGz / TOTAL_MEASUREMENTS;
}

static void correct_data(IMU_t* imu)
{
	imu->imuData.accX = (imu->imuData.accX - imu->calibAx)/imu->LSB_g;
	imu->imuData.accY = (imu->imuData.accY - imu->calibAy)/imu->LSB_g;
	imu->imuData.accZ = (imu->imuData.accZ - imu->calibAz)/imu->LSB_g;

	imu->imuData.gyroX = (imu->imuData.gyroX - imu->calibGx)/imu->LSB_deg_s * 0.01745329; //deg to rad
	imu->imuData.gyroY = (imu->imuData.gyroY - imu->calibGy)/imu->LSB_deg_s * 0.01745329;
	imu->imuData.gyroZ = (imu->imuData.gyroZ - imu->calibGz)/imu->LSB_deg_s * 0.01745329;
}

static void startPins(IMU_t* imu)
{
	if (imu->address == ADDRESS_HIGH)
	{
		HAL_GPIO_WritePin(
			imu->addressPin,
			imu->addressPinVal,
			GPIO_PIN_SET
		);
	}
	else
	{
		HAL_GPIO_WritePin(
			imu->addressPin,
			imu->addressPinVal,
			GPIO_PIN_RESET
		);
	}
}

static bool initialize(IMU_t* imu)
{
	IMU_sleepMode(imu, false);
	IMU_resetRegisters(imu);
	IMU_disableTemp(imu, false);
	IMU_setFullScaleAccel(imu, ACCEL_FULLSCALE_16);
	IMU_setFullScaleGyro(imu, GYRO_FULLSCALE_1000);
	IMU_selectClockSource(imu, INTERNAL_8MHZ);
	calibrate_imu(imu);

	if(!IMU_selfTest(imu))
	{
		return INIT_FAIL;
	}

	return INIT_SUCCESS;
}

static double factoryTrimGyro(uint8_t testVal)
{
  return 25 * 131 * pow(1.046, testVal-1);
}

static double factoryTrimAccel(uint8_t testVal)
{
  return 4096 * 0.34 * pow((0.92/0.34), (testVal-1)/(pow(2,5)-2));
}


