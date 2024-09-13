void SalvarTelemetria(){
  calcular_eixos_giroscopio();
  double Temperatura = bmp.readTemperature();
//  for(int x = 0; x <= 3; x++){
////    while(All_sat[1] == -999 && All_sat[2] == -999){
//      GPS_all_Data();
////    }
//  


  SD.remove("send.txt");

  Save("send","<p>");
  Save("send",String(All_sat[3]));
  Save("send","<\p>");
  Save("send","<p>");
  Save("send",String(All_sat[4]));
  Save("send","<\p>");
  Save("send","<p>");
  Save("send",String(All_sat[5]));
  Save("send","<\p>");
  Save("send","<p>");
  Save("send",String(All_sat[6]));
  Save("send","<\p>");
  Save("send","<p>");
  Save("send",String(All_sat[7]));
  Save("send","<\p>");
  Save("send","<p>");
  Save("send",String(All_sat[1]));
  Save("send","<\p>");
  Save("send","<p>");
  Save("send",String(All_sat[2]));  
  Save("send","<\p>");
  Save("send","<p>");
  Save("send",String(Temperatura));
  Save("send","<\p>");
  Save("send","<p>");
  Save("send",String(horizontal));
  Save("send","<\p>");
  Save("send","<p>");
  Save("send",String(vertical));
  Save("send","<\p>");
  Save("send","<p>");
  Save("send",String(eixoz));
  Save("send","<\p>");
  Save("send","<p>");
  
  Save("send","{");


  for(int t = 0; t <= 4; t++){
    String leroleoarquivoT = LerOleoArquivo(t);
    if(leroleoarquivoT != "fim"){
      Save("send","imagem ");
      Save("send",leroleoarquivoT);
      Save("send",": ");      
      Save("send","\t");
      Save("send",PegarDadosImagem(leroleoarquivoT.toInt()));
    }
    else{
      t = 5;
    }
    Serial.println(t);
  }
  Saveln("send","}");  
  Save("send","<\p>");
  //-----------salvar historico na telemetria--------------//  
  Save("Telemetria",String(All_sat[3]));
  Save("Telemetria","\t");
  Save("Telemetria",String(All_sat[4]));
  Save("Telemetria","\t");
  Save("Telemetria",String(All_sat[5]));
  Save("Telemetria","\t");
  Save("Telemetria",String(All_sat[6]));
  Save("Telemetria","\t");
  Save("Telemetria",String(All_sat[7]));
  Save("Telemetria","\t");
  Save("Telemetria",String(All_sat[1]));
  Save("Telemetria","\t");
  Save("Telemetria",String(All_sat[2]));  
  Save("Telemetria","\t");  
  Save("Telemetria",String(Temperatura));
  Save("Telemetria","\t");
  Save("Telemetria",String(horizontal));
  Save("Telemetria","\t");
  Save("Telemetria",String(vertical));
  Save("Telemetria","\t");
  Save("Telemetria",String(eixoz));
  Save("Telemetria","\t");
  Save("Telemetria","{");


  for(int t = 0; t <= 4; t++){
    String leroleoarquivoT = LerOleoArquivo(t);
    if(leroleoarquivoT != "fim"){
      Save("Telemetria",leroleoarquivoT);
      Save("Telemetria","\t");
      Save("Telemetria",PegarDadosImagem(leroleoarquivoT.toInt()));
    }
    else{
      t = 5;
    }
    Serial.println(t);
  }

  Saveln("Telemetria","}");  

}
