#include "MPU_6050_Driver.hpp"

MPU_6050::MPU_6050(bool setAddressHigh, I2C_HandleTypeDef* hi2c_in,
  GPIO_TypeDef* addressPinReg, uint16_t addressPin)
{
  if (setAddressHigh)
  {
    address = ADDRESS_HIGH;
    HAL_GPIO_WritePin(addressPinReg, addressPin, GPIO_PIN_SET);
  }

  hi2c = hi2c_in;
} 

bool MPU_6050::initialize()
{
  sleepMode(false);
  while (!resetRegisters()) {}
  disableTemp(true);
  selectClockSource(INTERNAL_8MHZ);
  if (!selfTest())
  {
    return INIT_FAIL;
  }
  return INIT_SUCCESS;
}

double factoryTrimGyro(uint8_t testVal)
{
  return 25 * 131 * pow(1.046, testVal-1);
}

double factoryTrimAccel(uint8_t testVal)
{
  return 4096 * 0.34 * pow((0.92/0.34), (testVal-1)/(pow(2,5)-2));
}

bool MPU_6050::selfTest()
{
  uint8_t test_recv[4];

  float GyroXDisabled, GyroYDisabled, GyroZDisabled;
  float AccelXDisabled, AccelYDisabled, AccelZDisabled;
  
  uint8_t normalMeas = 0b00011000;
  HAL_I2C_Mem_Write_DMA(hi2c, address, GYRO_CONFIG, sizeof(GYRO_CONFIG),
    &normalMeas, sizeof(normalMeas));

  readAccelRegisters();
  readGyroRegisters();

  GyroXDisabled = imuData->gyroX;
  GyroYDisabled = imuData->gyroY;
  GyroZDisabled = imuData->gyroZ;

  AccelXDisabled = imuData->accX;
  AccelYDisabled = imuData->accY;
  AccelZDisabled = imuData->accZ;

  float StrGyroX, StrGyroY, StrGyroZ;
  float StrAccelX, StrAccelY, StrAccelZ;

  uint8_t selfTest = 0b11111000;
  HAL_I2C_Mem_Write_DMA(hi2c, address, GYRO_CONFIG, 1,
    &selfTest, sizeof(selfTest));

  osDelay(1);

  StrGyroX = imuData->gyroX - GyroXDisabled;
  StrGyroY = imuData->gyroY - GyroYDisabled;
  StrGyroZ = imuData->gyroZ - GyroZDisabled;

  StrAccelX = imuData->accX - AccelXDisabled;
  StrAccelY = imuData->accY - AccelYDisabled;
  StrAccelZ = imuData->accZ - AccelZDisabled;

  HAL_I2C_Mem_Write_DMA(hi2c, address, GYRO_CONFIG, 1,
    &normalMeas, sizeof(normalMeas));

  HAL_I2C_Mem_Read_DMA(hi2c, address, SELF_TEST_X, 1,
    test_recv, 4);
  
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

  bool passAccX = abs(accXRes) < 14;
  bool passAccY = abs(accYRes) < 14;
  bool passAccZ = abs(accZRes) < 14;

  bool passGyroX = abs(gyroXRes) < 14;
  bool passGyroY = abs(gyroYRes) < 14;
  bool passGyroZ = abs(gyroZRes) < 14;

  return passAccX && passAccY && passAccZ && passGyroX
    && passGyroY && passGyroZ;
}

void MPU_6050::setSampleRate(uint16_t sample_rate_hz)
{
  uint8_t rate_divider = (GYRO_OUTPUT_RATE_HZ / sample_rate_hz) - 1;
  HAL_I2C_Mem_Write_DMA(hi2c, address, SMPLRT_DIV, 1,
    &rate_divider, 1);
}

void MPU_6050::setFullScaleGyro(Gyro_FullScale gyro_fs_setting)
{
  uint8_t config = gyro_fs_setting << 3;
  HAL_I2C_Mem_Write_DMA(hi2c, address, GYRO_CONFIG, 1,
    &config, 1);
}

void MPU_6050::setFullScaleAccel(Accel_FullScale accel_fs_setting)
{
  uint8_t config = accel_fs_setting << 3;
  HAL_I2C_Mem_Write_DMA(hi2c, address, ACCEL_CONFIG, 1,
    &config, 1);
}


void MPU_6050::readAccelRegisters()
{
  int16_t accelX, accelY, accelZ;
  uint8_t accelRec[6];

  HAL_I2C_Mem_Read_DMA(hi2c,address,ACCEL_XOUT_H, 1,
    accelRec, 6);
  
  accelX = (int16_t)(accelRec[0] << 8 | accelRec[1]);
  accelY = (int16_t)(accelRec[2] << 8 | accelRec[3]);
  accelZ = (int16_t)(accelRec[4] << 8 | accelRec[5]);

  imuData->accX = accelX;
  imuData->accY = accelY;
  imuData->accZ = accelZ;
}

void MPU_6050::readGyroRegisters()
{
  int16_t gyroX, gyroY, gyroZ;
  uint8_t gyroRec[6];

  HAL_I2C_Mem_Read_DMA(hi2c,address,GYRO_XOUT_H, 1,
    gyroRec, 6);
  
  gyroX = (int16_t)(gyroRec[0] << 8 | gyroRec[1]);
  gyroY = (int16_t)(gyroRec[2] << 8 | gyroRec[3]);
  gyroZ = (int16_t)(gyroRec[4] << 8 | gyroRec[5]);

  imuData->gyroX = gyroX;
  imuData->gyroY = gyroY;
  imuData->gyroZ = gyroZ;
}

void MPU_6050::readTempRegisters()
{
  int16_t temp;
  uint8_t tempRecv[2];

  HAL_I2C_Mem_Read_DMA(hi2c, address, TEMP_OUT_H, 1, 
    tempRecv, 2);

  temp = (int16_t)(tempRecv[0] << 8 | tempRecv[1]);
  temp = temp / 340 + 36.53;

  imuData->temp = temp;
}

void MPU_6050::updateData()
{
  readTempRegisters();
  readGyroRegisters();
  readAccelRegisters();
}

void MPU_6050::resetRegisters()
{
  uint8_t resetRegisters = 0b00000111;
  HAL_I2C_Mem_Write_DMA(hi2c, address, SIGNAL_PATH_RESET, 1,
    &resetRegisters, 1);
}


IMU_Data* MPU_6050::generateNewResult()
{
  updateData();
  return imuData;
}