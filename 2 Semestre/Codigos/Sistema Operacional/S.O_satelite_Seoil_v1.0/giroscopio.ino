void calcular_eixos_giroscopio()
{
  mpu6050.update();
  horizontal = (atan2(mpu6050.getAngleX(),mpu6050.getAngleZ()) + PI) * RAD_TO_DEG;
  vertical = (atan2(mpu6050.getAngleX(),mpu6050.getAngleY()) + PI) * RAD_TO_DEG;
  eixoz =  (atan2(mpu6050.getAngleY(),mpu6050.getAngleZ()) + PI) * RAD_TO_DEG;
  //delay (500);
}
