void GPS_all_Data(){
  int procurar = 0;
  /*
  ----------------------
  -   0 - satelite     -
  -   1 - lat          -
  -   2 - lng          -
  -   3 - dia          -
  -   4 - mes          -
  -   5 - ano          -
  -   6 - horas        -
  -   7 - minutos      -
  ----------------------  
  */
  All_sat[0] = 0;
  
  while(All_sat[0] < 1 or procurar < 10){
    procurar++;
    while(gpsSerial.available() > 0){
      if(gps.encode(gpsSerial.read())){
        All_sat[0] = gps.satellites.value(); // numero de satelites encontrados
        
        if(gps.location.isValid()){ // verifica se a localização esta valida
          All_sat[1] = (gps.location.lat());
          All_sat[2] = (gps.location.lng());
        }
        else{
          All_sat[1] = -999;
          All_sat[2] = -999;
        }
        
        if (gps.date.isValid()){
          All_sat[3] = gps.date.day();
          All_sat[4] = gps.date.month();
          All_sat[5] = gps.date.year();
        }
        else
        {
          All_sat[3] = -1;
          All_sat[4] = -1;
          All_sat[5] = -1;  
        }
      
        if(gps.time.isValid()){
          All_sat[6] = gps.time.hour() + 21;
          All_sat[7] = gps.time.minute();
        }
        else
        {
          All_sat[6] = -999;
          All_sat[7] = -999;
        }
      
        TextGps = ("sat: " + String(All_sat[0]) + '\n' + "LAT: " + String(All_sat[1],8) + '\n' + "LNG: " + String(All_sat[2],8) + '\n' + "Data: " + String(All_sat[3]) + "/" + String(All_sat[4]) + "/" + String(All_sat[5]) + '\n' + "Hora: " + String(All_sat[6]) + ":" + String(All_sat[7]));
        Serial.println(TextGps);
      }
    }
  }
  if (procurar >= 10){
    Serial.println("erro ao encontrar o gps");
      All_sat[0] = -1;
      All_sat[1] = -23.21301183;
      All_sat[2] = -46.79817920;
  }
}
