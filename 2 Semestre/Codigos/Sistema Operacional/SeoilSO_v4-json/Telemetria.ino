void Telemetria(){
  calcular_eixos_giroscopio();
  
  double Temperatura = bmp.readTemperature();
  double pressao = bmp.readPressure();

  if(isnan(Temperatura)){
    Temperatura = 0;  
  }
  if(isnan(pressao)){
    pressao = 0;  
  }
  
  double bateria = (((analogRead(A0) * 0.0082)-6)/2)*100;
  String mensagem;
  
//  for(int x = 0; x <= 3; x++){
////    while(All_sat[1] == -999 && All_sat[2] == -999){
//      GPS_all_Data();
////    }


  SD.remove("Send.txt");
  mensagem += "[[" + String(All_sat[3]) + "," + String(All_sat[4]) + "," + String(All_sat[5]) + "," + String(All_sat[6]) + "," + String(All_sat[7]) + ",";
  mensagem += String(All_sat[1]) + "," + String(All_sat[2]) + ",";
  mensagem += String(Temperatura) + ",";
  mensagem += String(pressao) + ",";
  mensagem += String(bateria) + ",";
  mensagem += String(ALL_Gyro[0]) + ",";
  mensagem += String(ALL_Gyro[1]) + ",";
  mensagem += String(ALL_Gyro[3]) + ",";      
  mensagem += String(ALL_Gyro[4]) + ",";
  mensagem += String(ALL_Gyro[5]) + "],";

  for(int t = 0; t <= 4; t++){
    String leroleoarquivoT = LerOleoArquivo(t);

    if(leroleoarquivoT != "fim"){
      mensagem += "{\"Img\": " + leroleoarquivoT + ",";
      mensagem += "\"dado\": \"" + PegarDadosImagem(leroleoarquivoT.toInt()) + "\"}";
    }
    else{
      t = 5;
    }
    if(t < 4){
      mensagem += ",";
    }

  }
  mensagem += "]"; 
  
  Serial.println(mensagem);  
  Saveln("Send",mensagem);  


  if (vezes >= 3){
    SD.remove("telemetria.txt");
    vezes = 0;
  }
  Save("telemetria","<tr>");
  
  Save("telemetria","<td>");
  Save("telemetria",String(All_sat[3]));
  Save("telemetria"," ");
  Save("telemetria",String(All_sat[4]));
  Save("telemetria"," ");
  Save("telemetria",String(All_sat[5]));
  Save("telemetria","</td>");
  
  Save("telemetria","<td>");
  Save("telemetria",String(All_sat[6]));
  Save("telemetria"," ");
  Save("telemetria",String(All_sat[7]));
  Save("telemetria","</td>");
  
  Save("telemetria","<td>");
  Save("telemetria",String(All_sat[1]));
  Save("telemetria"," ");
  Save("telemetria",String(All_sat[2]));  
  Save("telemetria","</td>");
  
  Save("telemetria","<td>");
  Save("telemetria",String(Temperatura));
  Save("telemetria","</td>");
  Save("telemetria","<td>");
  Save("telemetria",String(pressao));
  Save("telemetria","</td>");
  Save("telemetria","<td>");
  Save("telemetria",String(bateria));
  Save("telemetria","</td>");
  
  Save("telemetria","<td>");
  Save("telemetria",String(ALL_Gyro[0]));
  Save("telemetria"," ");
  Save("telemetria",String(ALL_Gyro[1]));
  Save("telemetria"," ");
  Save("telemetria",String(ALL_Gyro[2]));
  Save("telemetria"," ");
  Save("telemetria",String(ALL_Gyro[3]));
  Save("telemetria"," ");
  Save("telemetria",String(ALL_Gyro[4]));
  Save("telemetria"," ");
  Save("telemetria",String(ALL_Gyro[5]));
  Save("telemetria","</td>");
    
  Save("telemetria","<td>");
  Save("telemetria","{");

  for(int t = 0; t <= 4; t++){
    String leroleoarquivoT = LerOleoArquivo(t);
    if(leroleoarquivoT != "fim"){
      Save("telemetria","imagem ");
      Save("telemetria",leroleoarquivoT);
      Save("telemetria",": ");      
      Save("telemetria","\t");
      Save("telemetria",PegarDadosImagem(leroleoarquivoT.toInt()));
    }
    else{
      t = 5;
    }
    Serial.println(t);
  }
  Save("telemetria","}");  
  Saveln("telemetria","</td>");
  vezes++;
  

}
