//=======================gravando e lendo=================================//
/*
//gravar arquivos no esp -----------------------------------
void gravar(String state, String path)
{
  File rFile = SPIFFS.open(path,"w+");
  if(!rFile)
  {
    Serial.println("erro 01 - arquivo nao encontrado");
  }
  else
  {
    rFile.println(state);
  }
  rFile.close();
}

// 1er os arquivos esp   
String leroarq(String path) // ler o arquivo x
{
  File rFile = SPIFFS.open(path,"r");
  if(!rFile)
  {
    Serial.println("erro 01 - arquivo nao encontrado");
  }
  String content = rFile.readStringUntil('\r');
  //Serial.println(content);
  rFile.close();
  return content;
}

//abrir o spiffs -----------------------------------
void openFS(void){
  //Abre o sistema de arquivos
  if(!SPIFFS.begin()){
    Serial.println("\nErro ao abrir o sistema de arquivos");
  } else {
    Serial.println("\nSistema de arquivos aberto com sucesso!");
  }
}

  ant = leroarq("/leitura.txt");
  voo = leroarq("/voos.txt").toInt();
  Serial.println("voos salvos: " + String(voo));
  Serial.println ("somente leitura: "+String(desl));v
*/
