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
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

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


//=======================Sensores========================= //
//-------------------GPS-----------------------//
int GPSBaud = 9600;
float All_sat[8];

float SD_Analise[3];
float Em_Analise[3];

String Resultado = "null";

String TextGps = "null";
//----------eixos do giroscopio-------------//
double vertical;
double horizontal;
double eixoz;

double altitude;
//-----------objetos------------//

TinyGPSPlus gps;
SoftwareSerial gpsSerial(D4, D0);

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
  
  Serial.begin(9600);

  Serial.println("wire begin");
  Wire.begin();
  Wire.setClock(400000); //deixar o clock do wire para 400kHz
  iniciar_componentes();
  mostrarCOMPnoSerial();
  
  if(sd_conectado == true){
    sat_mode = lerSD_linha("Tirar_Fotos",1);
    Serial.println("dado lido: " + String(sat_mode) );
  }
  else{
    sat_mode = "0";  
  }
  //openFS();  
  

}

//=========================loop=============================//

void loop(){ 

  print_Cam_save();
  delay(100);
/*  if (Em_Analise[1] == 0 && Em_Analise[2] == 0){
    GPS_all_Data();
    Em_Analise[1] = (All_sat[1]);
    Em_Analise[2] = (All_sat[2]); 
  }
  else{
    Serial.println("analise");
    bool L = false;
    bool T = false;
    int lines = 2;
    for(int i = 0; i < lines; i++){
      
      if( i % 2 == 0){
        String AnaliseSD = lerSD_linha("Tirar_Fotos",i);
        Serial.println(AnaliseSD + " " + Em_Analise[1]);
        SD_Analise[1] = AnaliseSD.toInt();
        if(Em_Analise[1] > SD_Analise[1] - 0.0001 && Em_Analise[1] < SD_Analise[1] + 0.0001){
          T = true;
        }
      }
      else{
        String AnaliseSD = lerSD_linha("Tirar_Fotos",i);
        SD_Analise[2] = AnaliseSD.toInt();
        Serial.println(AnaliseSD + " " + Em_Analise[2]);
        if(Em_Analise[2] > SD_Analise[2] - 0.0001 && Em_Analise[2] < SD_Analise[2] + 0.0001){
          L = true;
        }
      }
      delay(100);
    }
    if(T == true && L == true){
      Serial.println("Tirar_Fotos");
    }
    else{T = false; L = false;}

    for(int i = 0; i < lines; i++){
      
      if( i % 2 == 0){
        String AnaliseSD = lerSD_linha("Enviar_Fotos",i);
        Serial.println(AnaliseSD + " " + Em_Analise[1]);
        SD_Analise[1] = AnaliseSD.toInt();
        if(Em_Analise[1] > SD_Analise[1] - 0.0001 && Em_Analise[1] < SD_Analise[1] + 0.0001){
          T = true;
        }
      }
      else{
        String AnaliseSD = lerSD_linha("Enviar_Fotos",i);
        Serial.println(AnaliseSD + " " + Em_Analise[2]);
        SD_Analise[2] = AnaliseSD.toInt();
        if(Em_Analise[2] > SD_Analise[2] - 0.0001 && Em_Analise[2] < SD_Analise[2] + 0.0001){
          L = true;
        }
      }
      delay(100);
    }
    if(T == true && L == true){
      Serial.println("Enviar_Fotos");
    }
    else{T = false; L = false;}
  }
  //delay(1000);*/
}


//========================Tarefas=============================//
void iniciar_componentes(){
  
  gpsSerial.begin(GPSBaud);
    
  iniciarSD();
  Iniciar_Cam();
  
  mpu6050.begin();
  giroscopio_conectado = true;
  
  
  if(bmp.begin(0x76)){
    Barometro_conectado = true;
  }   
}

void mostrarCOMPnoSerial(){
  Serial.println("camera - " + String(camera_conectado));
  Serial.println("GPS - "+ String(GPS_conectado));
  Serial.println("Barometro - " + String(Barometro_conectado));
  Serial.println("Giroscopio - "+ String(giroscopio_conectado));
  Serial.println("Lora - " + String(Lora_conectado));
  Serial.println("SD card - "+ String(sd_conectado));
}
