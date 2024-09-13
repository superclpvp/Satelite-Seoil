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

String lerSD_linha(String arquivo , int linha, int characteres){
  String debug;
  String saida;
  linha = linha-1;
  characteres = characteres + 3;
  File dataFile = SD.open(arquivo+".txt");    
  dataFile.seek(9 +(linha*characteres));
  saida = dataFile.readStringUntil(';');
  dataFile.close();
  return(saida);
}

int LerSD_QNTD_Caracteres(String arquivo){
  String debug;
  File dataFile = SD.open(arquivo+".txt");
  dataFile.seek(5);
  debug = dataFile.readStringUntil('\r');
  dataFile.close();
  return(debug.toInt());
}
int LerSD_QNTD_Dados(String arquivo){
  String debug;
  File dataFile = SD.open(arquivo+".txt");    
  dataFile.seek(0);
  debug = dataFile.readStringUntil('\r');
  dataFile.close();
  return(debug.toInt());
}
