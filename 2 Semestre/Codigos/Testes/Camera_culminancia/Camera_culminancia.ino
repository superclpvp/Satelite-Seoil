#include <Wire.h>

#include "MLX90640_API.h"
#include "MLX90640_I2C_Driver.h"

#define Botao D5
#define LED D6

const byte MLX90640_address = 0x33; //Default 7-bit unshifted address of the MLX90640

#define TA_SHIFT 8 //Default shift for MLX90640 in open air

float mlx90640To[768];
paramsMLX90640 mlx90640;

void setup()
{
  Wire.begin();
  Wire.setClock(400000); //Increase I2C clock speed to 400kHz

  Serial.begin(115200); //Fast serial as possible
  Iniciar_camera();

  pinMode(LED, OUTPUT);
  pinMode(Botao,INPUT);
  
}

void loop()
{

 if(digitalRead(Botao) == 1){
  digitalWrite(LED,HIGH);
  delay(100);
  digitalWrite(LED,LOW);
  delay(100);
  Tirar_foto();
  digitalWrite(LED,HIGH);
  delay(100);
  digitalWrite(LED,LOW);
  delay(100);
 }
 delay(1);
}
