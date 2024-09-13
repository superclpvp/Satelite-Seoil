//=========================Bibliotecas===============================//
#include <FS.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
//#include "MS5611.h"
//#include "SPIFFS.h"
#include <Adafruit_Sensor.h> 
#include <Adafruit_BMP280.h> 
#include "DHT.h"
 
//=========================variaveis===============================//

int modo_atual = 0; //variavel que muda o estado do satélite 

// sensores //

//----------eixos do giroscopio-------------//
double vertical;
double horizontal;
double eixoz;

double altitude;
//-----------objetos------------//
MPU6050 mpu6050(Wire);
Adafruit_BMP280 bmp; //OBJETO DO TIPO Adafruit_BMP280 (I2C)
#define DHTPIN 2 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
//----------//
uint32_t start; 
uint32_t stop;
//----------//


//========================setup================================//

void setup() {
  
  Serial.begin(115200);

  Serial.println("wire begin");
  Wire.begin();

  Serial.println("MPU6050 begin");
  mpu6050.begin();
  
  Serial.println("bmp begin");
  bmp.begin(0x76);
  
  Serial.println("DHT11 begin");
  dht.begin();
  
  Serial.println("mpu calculando");
  mpu6050.calcGyroOffsets(true);


  //openFS();  
  for(int i = 0; i <= 20; i++){
        Serial.println(" ");
  }
  Serial.println("----------------------------------");
  Serial.println("");
  Serial.println("Bem vindo ao sistema operacional seoil v1.0");
  Serial.println("");
  Serial.println("----comandos----");
  Serial.println("- Reset (rst) ---- resetar o satelite ----");
  Serial.println("- standby (stnd)  ---- utilize esse comando para voltar ao modo stand by ----");
  Serial.println("0 - modo atual (ma) ---- verificar o modo atual do satelite ----");
  Serial.println("1 - somente leitura (sml)---- Mostrar os valores do sensor da telemetria ----");
  Serial.println("----------------");
  Serial.println("");
  Serial.println("----------------------------------");
  Serial.println("");
}

//===========================loop=============================//

void loop() 
{   
  if(Serial.available())
  {
    Verificar_comandos();
  }  
  if(modo_atual == 1)
  {
    calcular_eixos_giroscopio();
    altitude == bmp.readAltitude(1013.25);
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    Serial.print("Humidade: " + String(h) + '\t' + "Temperatura: " + String(t)+ '\t');
    Serial.print("Altitude: " + String(bmp.readAltitude(1013.25),0 ) + '\t');
    Serial.println("eixo X: " + String(mpu6050.getAngleX()) + '\t' + "eixo Y: " + String(mpu6050.getAngleY()) + '\t' + "eixo Z: " + String(mpu6050.getAngleZ()));   
    delay(100);
  }

  
}
