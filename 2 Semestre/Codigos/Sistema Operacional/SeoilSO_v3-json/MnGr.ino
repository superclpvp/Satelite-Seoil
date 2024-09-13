int NumeroDeImagens(){
  int index_manager = 0;
  String buffer_manager;

  
  File ManagerCalvo = SD.open("Manager/M0Nimgs.txt");

  if(ManagerCalvo){
    Serial.println("abriu");
    buffer_manager = ManagerCalvo.readStringUntil('\r');


    ManagerCalvo.close();
  }
  else{
    Serial.println("não abriu");
  }
  
  return(buffer_manager.toInt());
}

void AdicionarImagem(){
  int index_manager = 0;
  String buffer_manager;

  
  File ManagerCalvo = SD.open("Manager/M0Nimgs.txt");

  if(ManagerCalvo){
    Serial.println("abriu");
    buffer_manager = ManagerCalvo.readStringUntil('\r');
    index_manager = buffer_manager.toInt();

    index_manager++;

    SD.remove("Manager/M0Nimgs.txt");

    ManagerCalvo.close();

    Save("Manager/M0Nimgs",String(index_manager));
  }
  else{
    Serial.println("não abriu");
  }
  
}

int LerManager(String Arq){
  
  int index_manager = 0;
  String buffer_manager;

  File ManagerCalvo = SD.open("Manager/"+Arq+".txt");

  if(ManagerCalvo){
    buffer_manager = ManagerCalvo.readStringUntil('\t');


    ManagerCalvo.close();
  }
  else{
    Serial.println("não abriu");
  }

  if(buffer_manager != "fim"){
    return(buffer_manager.toInt());  
  }
  else{
    return(-1);  
  }
}

void subManager(String Arq){
  
  int index_manager = 0;
  String buffer_manager;
  
  
  File ManagerCalvo = SD.open("Manager/"+Arq+".txt");
  if(ManagerCalvo){
  
  buffer_manager = ManagerCalvo.readStringUntil('\t');

  Serial.println(buffer_manager);
  if(buffer_manager =! "fim"){
    while (buffer_manager != ""){
       index_manager++;
       ManagerCalvo.seek(index_manager);
       buffer_manager = ManagerCalvo.readStringUntil('\t');
    }
    index_manager++;
    buffer_manager = ManagerCalvo.readStringUntil('\t');
    Save("tempMngr",buffer_manager);
    Save("tempMngr","\t");
    
    while(buffer_manager != "fim"){
      
      while (buffer_manager != ""){
         index_manager++;
         ManagerCalvo.seek(index_manager);
         buffer_manager = ManagerCalvo.readStringUntil('\t');
      }
      index_manager++;
      buffer_manager = ManagerCalvo.readStringUntil('\t');
      Save("tempMngr",buffer_manager);
      Save("tempMngr","\t");    
      
    }
    ManagerCalvo.close();
    SD.remove("Manager/"+Arq+".txt");
  
    File copiarColar = SD.open("tempMngr.txt");
    index_manager = 0;
    
    copiarColar.seek(index_manager);
    buffer_manager = copiarColar.readStringUntil('\t');
  
    Save("Manager/"+Arq,buffer_manager);
    Save("Manager/"+Arq,"\t");    
    
    while(buffer_manager != "fim"){
      while (buffer_manager != ""){
         index_manager++;
         copiarColar.seek(index_manager);
         buffer_manager = copiarColar.readStringUntil('\t');
      }
      index_manager++;
      buffer_manager = copiarColar.readStringUntil('\t');
      Save("Manager/"+Arq,buffer_manager);
      Save("Manager/"+Arq,"\t");    
      
    }
    copiarColar.close();
    SD.remove("tempMngr.txt");
    
    
    
    Serial.println("ok"); 
    }
  }
  else{
    Serial.println("não abriu");
  }
  
}

void addManager(String Arq , int ValorAdicionarManager){
  int index_manager = 0;
  String buffer_manager;
  
  
  File ManagerCalvo = SD.open("Manager/"+Arq+".txt");

  if(ManagerCalvo){
    Save("tempMngr",String(ValorAdicionarManager));
    Save("tempMngr","\t");
    
    buffer_manager = ManagerCalvo.readStringUntil('\t');
    Save("tempMngr",buffer_manager);
    Save("tempMngr","\t");
    
    while(buffer_manager != "fim"){
    
      while (buffer_manager != ""){
        index_manager++;
        ManagerCalvo.seek(index_manager);
        buffer_manager = ManagerCalvo.readStringUntil('\t');
      }
      index_manager++;
      buffer_manager = ManagerCalvo.readStringUntil('\t');
      Save("tempMngr",buffer_manager);
      Save("tempMngr","\t");    
    
    }
    ManagerCalvo.close();
    SD.remove("Manager/"+Arq+".txt");
    
    File copiarColar = SD.open("tempMngr.txt");
    index_manager = 0;
    
    copiarColar.seek(index_manager);
    buffer_manager = copiarColar.readStringUntil('\t');
    
    Save("Manager/"+Arq,buffer_manager);
    Save("Manager/"+Arq,"\t");    
    
    while(buffer_manager != "fim"){
      while (buffer_manager != ""){
        index_manager++;
        copiarColar.seek(index_manager);
        buffer_manager = copiarColar.readStringUntil('\t');
      }
      index_manager++;
      buffer_manager = copiarColar.readStringUntil('\t');
      Save("Manager/"+Arq,buffer_manager);
      Save("Manager/"+Arq,"\t");    
    
  }
  copiarColar.close();
  SD.remove("tempMngr.txt");
  
  
  
  Serial.println("ok"); 
  
  }
  else{
    Serial.println("não abriu");
  }  
}

bool DetectarTirarFoto(){
  int index_GPSfotos = 0;
  String buffer_GPSfotos;
  String buffer_ler_parte = "";

  bool LATD = false;
  bool LNGD = false;
    
  File GpsTirarFotos = SD.open("TirarFotos.txt");  

  if(GpsTirarFotos){
    Serial.println("abriu");
    for(int x = 0; x <= 3; x++){
//      while(All_sat[1] == -999 && All_sat[2] == -999){
        GPS_all_Data();
//      }
    }
    buffer_GPSfotos = GpsTirarFotos.readStringUntil('\r');  
    Serial.println(All_sat[1],5);
    Serial.println(All_sat[2],5);
    while(buffer_GPSfotos != "fim"){
      Serial.println(buffer_GPSfotos);
      buffer_ler_parte = buffer_GPSfotos.substring(0,buffer_GPSfotos.indexOf('\t')); 
    
      if(All_sat[1] < buffer_ler_parte.toFloat() + 0.0005 && All_sat[1] > buffer_ler_parte.toFloat() - 0.0005 ){
        LATD = true;
      }
      
      buffer_ler_parte = buffer_GPSfotos.substring(buffer_GPSfotos.indexOf('\t')); 
    
      if(All_sat[2] < buffer_ler_parte.toFloat() + 0.0005 && All_sat[2] > buffer_ler_parte.toFloat() - 0.0005 ){
        LNGD = true;
      }
  
      while(buffer_GPSfotos != ""){
        index_GPSfotos++;
        GpsTirarFotos.seek(index_GPSfotos);
        buffer_GPSfotos = GpsTirarFotos.readStringUntil('\r');
      }
      index_GPSfotos+=2;


      GpsTirarFotos.seek(index_GPSfotos);    
      buffer_GPSfotos = GpsTirarFotos.readStringUntil('\r');  
    
    }
  }
  else{
    Serial.println("erro");  
  }
  GpsTirarFotos.close();
  
  if(LNGD == true && LATD == true){
    Serial.println("true");
    return(true);
  }
  else{
    Serial.println("false");
    return(false);
  }
}

String PegarDadosImagem(int ende){
  int index_manager = 0;
  String buffer_manager;
  
  String Arq = "I"+String(ende);
  String DadoFinal = "";
  
  File PegarDados = SD.open(Arq+".txt");

  buffer_manager = PegarDados.readStringUntil('\r');  

  for(int x = 0; x <= 1; x++){
    while(buffer_manager != ""){
      index_manager++;
      PegarDados.seek(index_manager);
      buffer_manager = PegarDados.readStringUntil('\r');   
    }
    index_manager++;
  
    while(buffer_manager == ""){
      index_manager++;
      PegarDados.seek(index_manager);
      buffer_manager = PegarDados.readStringUntil('\r');   
    }
    index_manager++;
    PegarDados.seek(index_manager);
    buffer_manager = PegarDados.readStringUntil('\r');       
    

    DadoFinal += buffer_manager.substring(0,buffer_manager.indexOf('\r')-1) + " ";
  }
  return(DadoFinal);

  
}

String LerOleoArquivo(int injj) {
  int index_manager = 0;
  String LEROarquvio;

  File ManagerCalvo = SD.open("Manager/M3Oleos.txt");
  LEROarquvio = ManagerCalvo.readStringUntil('\t');
  
  if(ManagerCalvo){
//    if(injj == 0){
//      LEROarquvio = ManagerCalvo.readStringUntil('\t');
//    }
//    else{
      for(int c = 1; c <= injj; c++){
        while(LEROarquvio != ""){
          index_manager++;
          ManagerCalvo.seek(index_manager);
          LEROarquvio = ManagerCalvo.readStringUntil('\t');   
        }
        index_manager++;
        ManagerCalvo.seek(index_manager);
        LEROarquvio = ManagerCalvo.readStringUntil('\t');   
        
      }
//    }
//    Serial.println(LEROarquvio);

    ManagerCalvo.close();
  }
  return(LEROarquvio);  
  
}
