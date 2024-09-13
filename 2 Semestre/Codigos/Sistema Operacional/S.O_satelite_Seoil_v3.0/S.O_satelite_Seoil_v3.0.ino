//=========================Bibliotecas===============================//
#include <FS.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
//#include "MS5611.h"
//#include "SPIFFS.h"
#include <Adafruit_Sensor.h> 
#include <Adafruit_BMP280.h> 
#include "DHT.h"
#include <SD.h>
#include <SPI.h>

//======================bibliotecas personalizadas==================//

#include <MLX90640_API.h>
#include <MLX90640_I2C_Driver.h>
 
//=========================variaveis===============================//

String sat_mode = "0"; //variavel que muda o estado do satélite 
bool camera_conectado = false;
bool GPS_conectado = false;
bool Barometro_conectado = false;
bool giroscopio_conectado = false;
bool Lora_conectado = false;
bool sd_conectado = false;


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
#define CS_PIN  D8
//----------//
uint32_t start; 
uint32_t stop;
//----------//

//-----------Camera termica------------//
const int MLX90640_address = 0x33;

float mlx90640To[768];
paramsMLX90640 mlx90640;

#define TA_SHIFT 8 //Default shift for MLX90640 in open air

//----------//

//========================setup================================//

void setup() {
  
  Serial.begin(115200);

  Serial.println("wire begin");
  Wire.begin();
  Wire.setClock(400000); //deixar o clock do wire para 400kHz
  iniciar_componentes();
  if(sd_conectado == true){
    sat_mode = lerSD_linha("config",1);
  }
  else{
    sat_mode = "0";  
  }
  //openFS();  


}

//===========================loop=============================//

void loop() 
{   
  if(sat_mode == "0"){
    sleep();
  }  
  else if(sat_mode == "1"){
    Config();
  }
  else{
    all_commands();
    Serial.println("erro1 - satelite nao esta em nenhum modo");
  }
}

void iniciar_componentes(){
  
  iniciarSD();
  Iniciar_Cam();
  
  mpu6050.begin();
  giroscopio_conectado = true;
  
  
  if(bmp.begin(0x76)){
    Barometro_conectado = true;
  }   
}


void sleep(){
  Sleep_menu();
  while(sat_mode == "0"){
    if(Serial.available()){
      sleep_commands();
    }
  }
}

void Config(){
  Config_menu();
  while(sat_mode == "1")
  if(Serial.available()){
      config_commands();
    }
}
