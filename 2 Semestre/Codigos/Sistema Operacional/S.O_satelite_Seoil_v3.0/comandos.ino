void all_commands(){
  String command = Serial.readStringUntil('\n');
  if(command == "menu[]"){
    if(sat_mode == "0"){
      Sleep_menu();
    }
    if(sat_mode == "1"){
      Config_menu();
    }
  }
  if(command == "print"){
    print_Cam_save();
  }
  else if(command == "trocar_modo(000)"){
    sat_mode = "0";
  }
  else if(command == "trocar_modo(1)"){
    sat_mode = "1";
  }
  else if(command == "trocar_modo(2)"){
    sat_mode = "2";
  }
  else if(command == "trocar_modo(config)"){
    sat_mode = "config";
  }
  
}



//=================================menus===========================//
void Config_menu(){
Serial.println("-----------------------------------------------------config------------------------------------------------------------------------------");
Serial.println("");
Serial.println("1 - ao iniciar ficarei no modo - " + lerSD_linha("config",1));
Serial.println("2 - no modo telemetria salvarei tudo - " + lerSD_linha("config",2));
Serial.println("3 - no modo telemetria verificarei os dados a cada - " + lerSD_linha("config",3) + " segundo");
Serial.println("4 - no modo telemetria enviarei tudo para o lora - " + lerSD_linha("config",4));
Serial.println("5 - no modo normal ativarei a telemetria - " + lerSD_linha("config",5));
Serial.println("6 - no modo normal vou salvar os dados da telemetria a cada - " + lerSD_linha("config",6)+ " minutos");
Serial.println("");
Serial.println("no modo normal tenho as coordenadas:");
Serial.println("");
Serial.println("");
Serial.println("para mais coordenadas envie: new_cord(x,y) #somente numeros");
Serial.println("");
Serial.println("#para mudar configuracao mande o numero que quer editar");
}

void Sleep_menu(){
  Serial.println("----------------------------------------------------------bem vinde <3----------------------------------------------------------------");
  Serial.println("[estou em modo 0]");
  Serial.println("");
  Serial.println("camera - " + String(camera_conectado));
  Serial.println("GPS - "+ String(GPS_conectado));
  Serial.println("Barometro - " + String(Barometro_conectado));
  Serial.println("Giroscopio - "+ String(giroscopio_conectado));
  Serial.println("Lora - " + String(Lora_conectado));
  Serial.println("SD card - "+ String(sd_conectado));
  //GPS encontrando satelite
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("-------------------------------------------------------------------------------------------------------------------------------------------");
  Serial.println("");
  
Comandos();
  
  
}

void sleep_commands(){
  all_commands();
  
}
void config_commands(){

  String command1 = Serial.readStringUntil('\n');
  if(command1.substring(0,2) == "1 " ){
    Serial.println(command1.substring(2,3));
    Saveln("bkp",command1.substring(2,3));
    Saveln("bkp",lerSD_linha("config",2));
    Saveln("bkp",lerSD_linha("config",3));
    Saveln("bkp",lerSD_linha("config",4));
    Saveln("bkp",lerSD_linha("config",5));
    Saveln("bkp",lerSD_linha("config",6));
    SD.remove("config.txt");
    Saveln("config",lerSD_linha("bkp",1));
    Saveln("config",lerSD_linha("bkp",2));
    Saveln("config",lerSD_linha("bkp",3));
    Saveln("config",lerSD_linha("bkp",4));
    Saveln("config",lerSD_linha("bkp",5));
    Saveln("config",lerSD_linha("bkp",6));
    SD.remove("bkp.txt");
  }

  all_commands();
}
void Comandos(){
Serial.println("------------------------------------------------------------comandos-------------------------------------------------------------------");
Serial.println("em qualquer modo:");
Serial.println("");
Serial.println("menu[]");
Serial.println("trocar_modo(1,2,3,0,config)");
Serial.println("");
Serial.println("modo telemetria:");
Serial.println("");
Serial.println("salvar_prox(numero de linhas que voce quer salvar proximo) -- saida -- os proximos arquivos serão salvos no arquivo(telemetria.txt) no numero (x)");
Serial.println("salvar_tudo # salva todos as proximas leituras. ");
Serial.println("carregar(numero do arquivo) -- saida -- mostrar no serial o arquivo");
Serial.println("enviar_arquivo([inteiro] ou [numero do arquivo])");
Serial.println("");
Serial.println("");
Serial.println("");
Serial.println("modo normal:");
Serial.println("");
Serial.println("send_history(11022029) --- saida --- o que tem no arquivo");
Serial.println("send_info_history_images(11022029) --- saida --- total 3 imagens: img1 (hora) img2 (hora) img3 (hora)");
Serial.println("send_image(11022029)[hora] -- manda a imagem especifica--");
Serial.println("send_all_history -- manda todos os arquivos");
Serial.println("send_all_images(11022029) -- manda todas as imagens do arquivo");
Serial.println("");
Serial.println("-------------------------------------------------------------------------------------------------------------------------------------------");

}
