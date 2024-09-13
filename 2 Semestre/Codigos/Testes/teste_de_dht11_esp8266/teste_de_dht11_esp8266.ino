#include <SD.h>

#define CS_PIN  D8

void setup() {
  Serial.begin(115200);

  if (!SD.begin(CS_PIN)){
    Serial.println("erro");
    return;
  }

  Serial.println("cartão ta bom rapaiz");
}

void loop() {
  File dataFile = SD.open("LOG.txt", FILE_WRITE);

  if (dataFile){
    
    dataFile.println("hello_world");
    dataFile.close();
    
  }
  else{Serial.println("nao achei o arquivo");}

  delay(2000);

}
