//=========================Bibliotecas===============================//

#include <MPU6050_tockn.h> //biblioteca para o Giroscopio
#include <Wire.h>// biblioteca para comunicação Serial I2C
#include <Adafruit_Sensor.h> //Biblioteca suporte para sensores da marca Adafruit
#include <Adafruit_BMP280.h> //Biblioteca do Barômetro
#include <SD.h> //Biblioteca do cartão SD
#include <SPI.h> //Biblioteca para comunicação serial SPI do cartão SD
#include <TinyGPS++.h> //Biblioteca Do GPS
#include <SoftwareSerial.h> //Biblioteca para comunicação serial TX e RX
#include <Arduino_KNN.h> //Biblioteca Para O algoritmo KNN

//======================bibliotecas personalizadas(download: )==================//

#include <MLX90640_API.h> 
#include <MLX90640_I2C_Driver.h> //bibliotecas da camêra termica (MLX90640_DaniMaster.zip)

//=========================variaveis Globbais===============================//

//--------KNN-----------//
const int INPUTS = 2; //Numero de dados para o treino do knn
const int CLASSES = 2;// duas classes - 0 agua _ 1 oleo
const int K = 3;// valor de quantas casas o knn vai analisar para definir os valores de agua e oleo

float pixel[2];

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
//--------objetos--------//
#define CS_PIN  D8 // pino do Chip Select(CS) do Cartão SD

KNNClassifier knn(INPUTS); // Objeto KNN

TinyGPSPlus gps;
SoftwareSerial gpsSerial(D4, D0);

MPU6050 mpu6050(Wire);
Adafruit_BMP280 bmp; //OBJETO DO TIPO Adafruit_BMP280 (I2C)

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
  SalvarTelemetria();
  TreinarKnn();

}
//=========================loop=============================//

void loop(){ 

  bool Tarefa_Comprida = false;
//  
//  if(DetectarTirarFoto()){
//    print_Cam_save();
//    Tarefa_Comprida = true;
//  }
//  else{
//    if(LerManager("M1ImgsNProcss") > -1){
//      ProcessarImagem(LerManager("M1ImgsNProcss"));
//      Tarefa_Comprida = true;
//    }
//    else if(LerManager("M2ImgsProcss") > -1 && Tarefa_Comprida == false){
//      Analisar_Imagem_KNN(LerManager("M2ImgsProcss"));
//      Tarefa_Comprida = true;      
//    }
//    
//    SalvarTelemetria();
//  }

  
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
