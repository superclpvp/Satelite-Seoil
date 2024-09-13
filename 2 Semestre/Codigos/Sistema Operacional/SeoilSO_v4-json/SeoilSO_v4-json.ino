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
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

//======================bibliotecas personalizadas(download: )==================//

#include <MLX90640_API.h> 
#include <MLX90640_I2C_Driver.h> //bibliotecas da camêra termica (MLX90640_DaniMaster.zip)

//=========================variaveis Globbais===============================//

//--------KNN-----------//
const int INPUTS = 2; //Numero de dados para o treino do knn
const int CLASSES = 2;// duas classes - 0 agua _ 1 oleo
const int K = 3;// valor de quantas casas o knn vai analisar para definir os valores de agua e oleo
int vezes = 3;

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
double ALL_Gyro[6];

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


const char* ssid = "Vegana";
const char* password = "yanna123";

ESP8266WebServer server(80);

//----------//

void handleRoot() {

  String textoHTML;
  textoHTML = "<link rel=stylesheet href=https://www.w3schools.com/w3css/4/w3.css>";
//textoHTML += "<style>table, td, th {th {text-align: left;}</style>";
  textoHTML += "<body class=w3-light-green>";
  textoHTML += "<h1><p align=center><b>Se<sup>2</sup>Oil: Satelite de Monitoramento de Manchas de oleo em rios, lagos e lagoas</b></p></h1></br>";
  //textoHTML += "<h1><p align=center>Satelite de Monitoramento de Manchas de oleo em rios, lagos e lagoas</p></h1></br>";
  textoHTML += "<p align=center></c><img src = https://v1.padlet.pics/1/image.webp?t=c_limit%2Cdpr_2%2Ch_508%2Cw_508&url=https%3A%2F%2Fstorage.googleapis.com%2Fpadlet-uploads%2F2021541202%2F69e135c62cbea44867e6b63b0fa9d051%2FWhatsApp_Image_2023_11_14_at_09_09_47.jpeg%3FExpires%3D1700568611%26GoogleAccessId%3D778043051564-q79bsd8mc40b0bl82ikkrtc3jdofe4dg%2540developer.gserviceaccount.com%26Signature%3DwxmJIIjlf2pzYfrGcJCjLFxoPhmYX196mj3XfeleoUbsNH6Xhemtb7qrHsn1iMDw%252BqVqS4wegAtN3ppjjfHYbkF7cr2fMexnmzi2xkvlZTqIY1k3uepZwco5h3Etdfl0RsGKMNCkteZMr%252BVfKqJc8WLvM9XmBKP0uWRKGV7pZQg%253D%26original-url%3Dhttps%253A%252F%252Fpadlet-uploads.storage.googleapis.com%252F2021541202%252F69e135c62cbea44867e6b63b0fa9d051%252FWhatsApp_Image_2023_11_14_at_09_09_47.jpeg width=200 height=200 />";  textoHTML += "<img src=data:image/png;base64,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 width=200 height=200></p>";
  textoHTML += "</br>";
  textoHTML += "<h2><p align=center><b>Dados do satelite</b></p></h2>";
  textoHTML += "</br>";
  textoHTML += "<table border=1 text-aling=left> <tr> <th> Data </th><th> Hora </th><th> Posicao Geografica</th> <th>Temperatura</th><th>Pressao</th><th>Bateria</th><th>Giroscopio</th> <th> Dados da camera termica</th> </tr>";
  textoHTML += ler_o_Send();
  textoHTML += "</table>";
  //textoHTML += "Clique para atualizar os dados</br>";
  //textoHTML +="BOTAO"; 
  //textoHTML +="</body>";
  server.send(200, "text/html", textoHTML);
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void iniciar_componentes(){
  
  gpsSerial.begin(GPSBaud);
    
  iniciarSD();
  Iniciar_Cam();
  
  mpu6050.begin();
  giroscopio_conectado = true;
  
  
  if(bmp.begin(0x76)){
    Barometro_conectado = true;
  }   


    WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}
//========================setup================================//

void setup() {
  
  Serial.begin(115200); // clock do ESP8266 

  Serial.println("wire begin");
  Wire.begin();
  Wire.setClock(400000); //deixar o clock do wire para 400kHz
  iniciar_componentes(); //tarefa para iniciar os componentes 
  mostrarCOMPnoSerial(); //imprimir no monitor serial os componentes disponiveis
  Telemetria();
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
//  }

  server.handleClient();
//  handleRoot();
  Telemetria();
//  Serial.println("a");
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
