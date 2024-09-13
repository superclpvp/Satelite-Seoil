void calcular_eixos_giroscopio()
{
  mpu6050.calcGyroOffsets(true);
  mpu6050.update();
  horizontal = mpu6050.getAngleX();
  vertical = mpu6050.getAngleX();
  eixoz = mpu6050.getAngleY();
  //delay (500);
} 
