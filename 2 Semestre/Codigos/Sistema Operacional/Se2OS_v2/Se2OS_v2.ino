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
#include <Arduino_KNN.h>

//======================bibliotecas personalizadas(download: )==================//

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
//-----------------KNN---------------//

int INPUTS = 230; //pixels na imagem
int Classes = 2; //com oleo/ sem oleo
int Imagens_Treino = 50;


const int K = 5;

KNNClassifier myKNN(INPUTS);

//-----------Camera termica------------//
const int MLX90640_address = 0x33;

float mlx90640To[768];
paramsMLX90640 mlx90640;

#define TA_SHIFT 8 //Default shift for MLX90640 in open air

//----------//
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
//========================setup================================//

void setup() {
  
  Serial.begin(115200); // clock do ESP8266 

  Serial.println("wire begin");
  Wire.begin();
  Wire.setClock(400000); //deixar o clock do wire para 400kHz
  iniciar_componentes(); //tarefa para iniciar os componentes 
  mostrarCOMPnoSerial(); //imprimir no monitor serial os componentes disponiveis

}
//=========================loop=============================//
int timer = 0;
void loop(){ 
  
  double bateria;
  double acumulador;
  double leiA0;
  double vMax = 3.3;

  //pegar as coordenadas do gps
  if (All_sat[0] == 0){
    Serial.println("ler o gps");
    GPS_all_Data();//esta função se localiza na aba #GPS#
  }
  else{
    calcular_eixos_giroscopio();
    if (camera_conectado == true){
      print_Cam_save();
    }

    //------monitoramento da bateria-------//
    //arquivo salvo em "saida.txt"
    if (timer < 10){
      delay(1000);
      timer ++;
      Serial.println(timer);
    }
    else{
      timer = 0;
      for(int i=0;i<=100;i++){
        leiA0 = (analogRead(A0)*vMax)/8.0;
        acumulador = acumulador + leiA0;
      }
      
      bateria = acumulador / 100;
      acumulador = 0;
      leiA0 = analogRead(A0);
      Serial.println(bateria);
      Saveln("saida",String(bateria));
    }
    
  }
}

//========================Tarefas=============================//


void mostrarCOMPnoSerial(){
  Serial.println("camera - " + String(camera_conectado));
  Serial.println("GPS - "+ String(GPS_conectado));
  Serial.println("Barometro - " + String(Barometro_conectado));
  Serial.println("Giroscopio - "+ String(giroscopio_conectado));
  Serial.println("Lora - " + String(Lora_conectado));
  Serial.println("SD card - "+ String(sd_conectado));
}
