void calcular_eixos_giroscopio()
{
//  mpu6050.calcGyroOffsets(true);
  mpu6050.update();
  ALL_Gyro[0] = mpu6050.getAngleX();
  ALL_Gyro[1] = mpu6050.getAngleY();
  ALL_Gyro[2] = mpu6050.getAngleZ();
  ALL_Gyro[3] = mpu6050.getAccX();
  ALL_Gyro[4] = mpu6050.getAccY();
  ALL_Gyro[5] = mpu6050.getAccZ();  
  //delay (500);
} 
