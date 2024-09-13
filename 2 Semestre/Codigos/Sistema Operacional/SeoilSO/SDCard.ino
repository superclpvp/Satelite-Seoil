void iniciarSD(){
  if (!SD.begin(CS_PIN)){
    Serial.println("erro");
    return;
  }

//  sd_conectado = true;
}

void Saveln(String arquivo, String texto){

  File dataFile = SD.open(arquivo + ".txt", FILE_WRITE);

  if (dataFile){
    dataFile.println(texto);
    dataFile.close();
    
  }

}

void Save(String arquivo, String texto){

  File dataFile = SD.open(arquivo + ".txt", FILE_WRITE);

  if (dataFile){
    dataFile.print(texto);
    dataFile.close();
    
  }

}
