#include "MPU_6050_Driver.hpp"
MPU_6050 currentMpu(4,1);
IMU_Data* data;
void setup()
{
  Serial.begin(9600);
  currentMpu.MPU_6050_begin(Wire);
}

void loop()
{
  data = currentMpu.generateNewResult();
  //currentMpu.getData(data);
  Serial.print(data->GyroX);
  Serial.print(",");
  Serial.print(data->GyroY);
  Serial.print(",");
  Serial.print(data->GyroZ);
  Serial.println(",");
}
