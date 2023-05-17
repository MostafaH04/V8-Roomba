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
    i2c_wire = I2Cpipe;
    i2c_wire.beginTransmission(address);
    i2c_wire.write(PWR_MGMT_1);
    i2c_wire.write(0x00);
    i2c_wire.endTransmission(true);
    fullScaleOperation(true);
}

IMU_Data* MPU_6050::generateNewResult()
{
    i2c_wire.beginTransmission(address);
    i2c_wire.write(GYRO_XOUT_H);
    i2c_wire.endTransmission(false);
    i2c_wire.requestFrom(address, 6, true);

    imuData->GyroX = (i2c_wire.read() << 8 | i2c_wire.read())/LSB_deg_s;
    imuData->GyroY = (i2c_wire.read() << 8 | i2c_wire.read())/LSB_deg_s;
    imuData->GyroZ = (i2c_wire.read() << 8 | i2c_wire.read())/LSB_deg_s;

    i2c_wire.beginTransmission(address);
    i2c_wire.write(ACCEL_XOUT_H);
    i2c_wire.endTransmission(false);
    i2c_wire.requestFrom(address, 6, true);
    imuData->AccX = (i2c_wire.read() << 8 | i2c_wire.read())/LSB_g;
    imuData->AccY = (i2c_wire.read() << 8 | i2c_wire.read())/LSB_g;
    imuData->AccZ = (i2c_wire.read() << 8 | i2c_wire.read())/LSB_g;

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
    i2c_wire.beginTransmission(address);
    i2c_wire.write(GYRO_CONFIG);
    i2c_wire.write(rangeSpec); // full scale range of gyroscope (+- 2000 deg/s)
    i2c_wire.endTransmission(true);
    
    // accel config
    i2c_wire.beginTransmission(address);
    i2c_wire.write(ACCEL_CONFIG);
    i2c_wire.write(rangeSpec);
    i2c_wire.endTransmission(true);
}
