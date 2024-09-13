void Save(String arquivo, String texto){

  File dataFile = SD.open(arquivo + ".txt", FILE_WRITE);

  if (dataFile){
    dataFile.print(texto);
    dataFile.close();
    
  }

}
void Saveln(String arquivo, String texto){

  File dataFile = SD.open(arquivo + ".txt", FILE_WRITE);

  if (dataFile){
    dataFile.println(texto);
    dataFile.close();
    
  }

}
void iniciarSD(){
  if (!SD.begin(CS_PIN)){
    Serial.println("erro");
    return;
  }

  sd_conectado = true;
}

String lerSD_linha(String arquivo, int linha){
  String saida;
  linha = linha-1;
  File dataFile = SD.open(arquivo+".txt");
  dataFile.seek(linha*3);
  saida = dataFile.readStringUntil('\r');
  dataFile.close();
  return(saida);
}
