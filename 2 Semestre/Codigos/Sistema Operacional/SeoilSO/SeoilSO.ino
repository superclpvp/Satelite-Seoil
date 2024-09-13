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

//--------objetos--------//
#define CS_PIN  D8 // pino do Chip Select(CS) do Cartão SD

KNNClassifier knn(INPUTS); // Objeto KNN

//===========================Void Setup=================================//
void setup() {
  Serial.begin(115200);//9600 para Arduino UNO - 1152000 para Esp8266
  iniciarSD();
  TreinarKnn();
  Iniciar_Cam();

  //-------place holder-------//
  ProcessarImagem(2);
  Analisar_Imagem_KNN(2);

}//Fim do Void Setup


//===========================Void Loop=================================//
void loop() {


}//Fim do Void loop
