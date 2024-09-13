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

void Rewrite_Tarefa(String command, int dado){
  String arch;

  if(command == "GPS"){
    arch = lerSD_linha("Tarefa",2, 8);
    SD.remove("Tarefa.txt");
    File dataFile = SD.open("Tarefa.txt", FILE_WRITE);    
    dataFile.println("000");
    dataFile.println("000");
    dataFile.println("000000" + String(dado) + ";");
    dataFile.println(arch + ";");
    dataFile.close();
  }
  if(command == "ADD_imagem"){
    arch = lerSD_linha("Tarefa",1, 8);
    String imagem = lerSD_linha("Tarefa",2, 8);
    int Num_imagem = imagem.toInt();
    Num_imagem = Num_imagem + dado;
    imagem = String(Num_imagem);
    SD.remove("Tarefa.txt");
    File dataFile = SD.open("Tarefa.txt", FILE_WRITE);    
    dataFile.println("000");
    dataFile.println("000");
    int aarch = arch.toInt();
    dataFile.println("000000" + String(aarch) + ";");
    dataFile.println(imagem + ";");
    dataFile.close();
  }
  if(command == "SUB_imagem"){
    arch = lerSD_linha("Tarefa",1, 8);
    String imagem = lerSD_linha("Tarefa",2, 8);
    int Num_imagem = imagem.toInt();
    Num_imagem = Num_imagem - dado;
    imagem = String(Num_imagem);
    SD.remove("Tarefa.txt");
    File dataFile = SD.open("Tarefa.txt", FILE_WRITE);    
    dataFile.println("000");
    dataFile.println("000");
    int aarch = arch.toInt();
    dataFile.println("000000" + String(aarch) + ";");
    dataFile.println(imagem + ";");
    dataFile.close();
  }
} 
