#include <SPI.h>
#include <SD.h>

#define CS_PIN D8
double sensor = 0;
int Tempo = 0;

File arquivo;
String Dado;
//SdFat SD;

void setup() {
  Serial.begin(115200);
  Serial.println("esp ta funcionando man...");
    if (!SD.begin(CS_PIN)){
    Serial.println("Erro ao inicializar o cartão SD");
    while(true){
      Serial.println("Erro ao inicializar o cartão SD");
    }
    
  }

  Serial.println("Cartão SD inicializado com sucesso");
  pinMode(A0,INPUT);

}

void loop() {
  String saida;

  Tempo = Tempo + 1;
  sensor = (analogRead(A0));
  sensor = sensor / 10;
  saida = "Teste";//String(Tempo) + ": " + String(sensor);
  

  Serial.println(saida);
  Saveln("",saida);
  
  delay(60000);
}

void Saveln(String nome, String texto){

  arquivo = SD.open("saidateste.txt", FILE_WRITE);

  if (arquivo){
    arquivo.println(texto);
    arquivo.close();
    
  }

}
