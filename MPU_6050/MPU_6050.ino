#include "MPU_6050_Driver/MPU_6050_Driver.cpp"
MPU_6050 currentMpu(6,1,1);
IMU_Data* data;
void setup()
{
  currentMpu.getData(data);
  Serial.begin(9600);
}

void loop()
{
  currentMpu.generateNewResult();
  Serial.print(data->AccX);
  Serial.print(",");
  Serial.print(data->AccY);
  Serial.print(",");
  Serial.print(data->AccZ);
  Serial.print(",");
}
