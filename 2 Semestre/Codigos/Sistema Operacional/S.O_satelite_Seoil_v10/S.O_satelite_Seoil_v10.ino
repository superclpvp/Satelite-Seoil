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

}
//=========================loop=============================//

void loop(){ 
  String GPS;
  String Estou;
  
  GPS = lerSD_linha("Tarefa",1, 8);

  if(GPS == "0"){
    Serial.print("verificar onde esta");
    Rewrite_Tarefa("GPS",1);
  }
  else if(Estou == "print"){
    Serial.println("tirar foto");
    print_Cam_save();
  }
  else if(Estou == "send"){
    Serial.println("Satelite envia dados");
  }
  else{
    String SD_Process = lerSD_linha("Tarefa",2, 8)  ;
    int Num_Process = SD_Process.toInt();

    while (Num_Process > 0){
      SD_Process = lerSD_linha("Tarefa",2, 8);
      Num_Process = SD_Process.toInt();

      Serial.println(Num_Process);      
      Serial.print("KNN analizando");

      Rewrite_Tarefa("SUB_imagem", 1);
    }
    Rewrite_Tarefa("GPS",0);
    Serial.println("GPS = 0, NOW I'M GOING TO SLEEP -_-");
    delay(1000);
    Serial.println("IM WAKE UP 0-0 Restarting the routine");
  }
}

String Verificar_Onde_Esta(){
//=======leitura das coordenadas==========//
  bool saida_Y = false;
  bool saida_X = false;
  int N_chart;
  int N_dados;
  float Numero_dado;
  String dado;

  N_chart = LerSD_QNTD_Caracteres("Tirar_Fotos");
  N_dados = LerSD_QNTD_Dados("Tirar_Fotos");
  GPS_all_Data();
  Serial.println("vei");
  for(int i = 1; i <= N_dados; i++){
    dado = lerSD_linha("Tirar_Fotos",i,N_chart);
    Numero_dado = dado.toFloat();
    if(i % 2 == 0){
      Serial.print("y: ");
      if(Numero_dado > All_sat[1] + 0.0001 && Numero_dado < All_sat[1] - 0.0001  ){
        Serial.print(" loc ");   
        saida_Y = true;  
      }
      
    }
    else{
      Serial.print("x: "); 
      if(Numero_dado > All_sat[1] + 0.0001 && Numero_dado < All_sat[1] - 0.0001  ){
        Serial.print(" loc "); 
        saida_X = true;          
      }
    }
    Serial.println(Numero_dado,8);
  }  
  
  if(saida_X == true && saida_Y == true){
    return("print");
      
  }
  else{
    return("null");
    
  }
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
