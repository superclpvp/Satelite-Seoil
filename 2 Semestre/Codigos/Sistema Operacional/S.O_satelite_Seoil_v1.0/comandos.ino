void Verificar_comandos(){
  String command = Serial.readStringUntil('\n');
  if(command == "ma" or command == "modo atual" or command == "0"){
    if(modo_atual == 0){
      Serial.println("estou no modo: stand by");
      Serial.println("");
    }
    if(modo_atual == 1){
      Serial.println("");
      Serial.println("estou no modo: somente leitura");
      Serial.println("dica: para desativar o modo somente leitura basta digitar (pare)");
      Serial.println("");
      delay(1000);
    }
  }
  if(command == "sml" or command == "somente leitura" or command == "1"){
    Serial.println("modo: somente leitura");
    Serial.println("");
    modo_atual = 1;
  }
  if(command == "standby" or command == "stnd"){
      Serial.println("");
      Serial.println("voltando para o modo stand by");
      Serial.println("");
      modo_atual = 0;
  }
  if(command == "reset" or command == "rst"){
    Serial.println("Sending Reset command");
    Serial.println(1/0);
  }
}

//=====================Comandos antigos=============================//
/*
   if (command == "ler" && desl == 0) // leitura ------------------
    {      
      if(ler == 0 && voo < maximovoo)
      {
        ler = 1;
        Serial.println("ler = 1");
      }
      else if(ler == 1)
      {
        Serial.println("ainda lendo...");
      }
      else
      {
        led01();
      }
    }

    if (command == "fd")// formatar ------------------
    {
      ant = "";
      voo = 0;
      SPIFFS.remove("/voos.txt");
      SPIFFS.remove("/leitura.txt");
      Serial.println("disco formatado com sucesso!");
    }

    if (command == "rl")// relatorio ------------------
    {
       String leitura = leroarq("/leitura.txt");
       Serial.println(leitura);
    }

    if (command == "sml")// somente leitura ------------------
    {
       if(desl == 0)
       {
        desl = 1;
        delay(10);
       }
       else
       {
        desl = 0;
        delay(10);
       }
              
    }
    
    if (command == "?")// nao sei os comandos ------------------
    {
       Serial.println("comandos: ler - (ler os arquivos) | fd - (formatar disco) | rl - (relatorio dos voos) | ? - (exibir comandos) | voo - (numero de voos) | sml - (somente leitura liga/desliga)");
    }

    if (command == "voo")// voos ------------------
    {
       Serial.println("voos salvos: " + String(voo)); 
    }
    */
