
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);
#include <Servo.h>   

Servo sg90;
int servo_pin = 2;          
int posicaoinicial=0;
int servoposinicial=0;
boolean calibracao=false;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  sg90.attach ( servo_pin );
  Serial.println();
  pinMode (13, OUTPUT);
}

void loop() {
  while (calibracao==false){
    digitalWrite(13, HIGH);
    mpu6050.update();
    posicaoinicial=mpu6050.getAccAngleX();
    Serial.print(" Calibracao anguloX : ");
    Serial.print(posicaoinicial);
    Serial.print ("\t");
    Serial.print("servoX : ");
    Serial.println(sg90.read());
    servoposinicial=sg90.read();
    calibracao=true;
    delay(5000);
  }
  digitalWrite(13, LOW);
  mpu6050.update();
  if (mpu6050.getAccAngleX()>posicaoinicial+3){
    servoposinicial=sg90.read();
    sg90.write (servoposinicial-1);
    mpu6050.update();
    Serial.print("Rotacionar anguloX : ");
    Serial.print(abs (mpu6050.getAccAngleX()));
    Serial.print ("\t");
    Serial.print("servoX : ");
    Serial.println(sg90.read());
    delay(10);
  }
  else if(mpu6050.getAngleX()<posicaoinicial-3){
    servoposinicial=sg90.read();
    sg90.write (servoposinicial+1);  
    mpu6050.update();
    Serial.print("Rotacionar -anguloX : ");
    Serial.print(abs (mpu6050.getAccAngleX()));
    Serial.print ("\t");
    Serial.print("servoX : ");
    Serial.println(sg90.read());
    delay(10);
  }
  else {
    Serial.print("anguloX : ");
    Serial.print(abs (mpu6050.getAccAngleX()));
    Serial.print ("\t");
    Serial.print("servoX : ");
    Serial.println(sg90.read());
    delay(1000);
  }
  
  
}//fim do loop
