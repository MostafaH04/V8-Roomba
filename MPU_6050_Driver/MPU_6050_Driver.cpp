#include "MPU_6050_Driver.hpp"

IMU_Data::IMU_Data(): AccX(0), AccY(0), AccZ(0), GyroX(0), GyroY(0), GyroZ(0) {}

MPU_6050::MPU_6050(uint8_t addressSet_in, bool setAddressHigh)
{
    addressSet = addressSet_in;
    pinMode(addressSet, OUTPUT);
    digitalWrite(addressSet, setAddressHigh);

    if (setAddressHigh)
        address = ADDRESS_HIGH;
    else
        address = ADDRESS_LOW;

    AccErrorX = AccErrorY = 0;
    GyroErrorX = GyroErrorY = GyroErrorZ = 0;

    LSB_g = 16384;
    LSB_deg_s = 131;

    imuData = new IMU_Data();
}

void MPU_6050::MPU_6050_begin(TwoWire I2Cpipe)
{
    Wire1 = I2Cpipe;
    Wire1.beginTransmission(address);
    Wire1.write(PWR_MGMT_1);
    Wire1.write(0x00);
    Wire1.endTransmission(true);
    fullScaleOperation(true);
}

IMU_Data* MPU_6050::generateNewResult()
{
    Wire1.beginTransmission(address);
    Wire1.write(GYRO_XOUT_H);
    Wire1.endTransmission(false);
    Wire1.requestFrom(address, 6, true);

    imuData->GyroX = (Wire1.read() << 8 | Wire1.read())/LSB_deg_s;
    imuData->GyroY = (Wire1.read() << 8 | Wire1.read())/LSB_deg_s;
    imuData->GyroZ = (Wire1.read() << 8 | Wire1.read())/LSB_deg_s;

    Wire1.beginTransmission(address);
    Wire1.write(ACCEL_XOUT_H);
    Wire1.endTransmission(false);
    Wire1.requestFrom(address, 6, true);
    imuData->AccX = (Wire1.read() << 8 | Wire1.read())/LSB_g;
    imuData->AccY = (Wire1.read() << 8 | Wire1.read())/LSB_g;
    imuData->AccZ = (Wire1.read() << 8 | Wire1.read())/LSB_g;

    return imuData;
}

void MPU_6050::fullScaleOperation(bool fullScale)
{
    uint8_t rangeSpec = 0x18;
    if (!fullScale)
        rangeSpec = 0x0;
    else
    {
        LSB_g = 2048;
        LSB_deg_s = 16.4;
    }
    // gyroscope config
    Wire1.beginTransmission(address);
    Wire1.write(GYRO_CONFIG);
    Wire1.write(rangeSpec); // full scale range of gyroscope (+- 2000 deg/s)
    Wire1.endTransmission(true);
    
    // accel config
    Wire1.beginTransmission(address);
    Wire1.write(ACCEL_CONFIG);
    Wire1.write(rangeSpec);
    Wire1.endTransmission(true);
}
