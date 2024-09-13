
/*
// variaveis de fisico //
long ler = 0; // essa variavel define quando o esp vai ler
int bota = 02; // porta de entrada do botão [ler]
int led = 13; // liga / desliga led
int desl = 0; //liga / desliga o modo somente leitura
int maxmetros;
int botas = 14;
//-----------------------//
int voo = 0; // coordenada [y]
String ant; // string valor anterior
int maximovoo = 1;
int comp;
*/

/*
//-------------------------botão-------------------------------//

    int lig = digitalRead(bota); // variavel estado do botão (NÃO MEXER)
    if(lig == 1 && desl == 0)
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
    
//-----------------------gravando os arquivos---------------------------------//
if (desl == 0)
{
  if(ler == 1)//O INT LER É PARA COMEÇAR A LEITURA 
  {
    ant =( ant + '\n' + "------------" + "VOO " + String(voo + 1) + "------------" ); //mostrar valor do voo

    ant = (ant + '\n' + "barometro inicio: " + String(bmp.readAltitude(1013.25),0));
    ant = (ant + '\n' + "bar" + '\t' + "Ax" + '\t' + "Ay" + '\t' + "Az" + '\t' + "Gx" + '\t' + "Gy" + '\t' + "Gz" );
    
    for(int i = 0; i <= 150 ; i++)// i <= 150 // 
    {
      ledH();
      delay(200);
      ledL();
      delay(200);
    }
    
    ledH();
    for(int i = 0; i <= 100 ; i++)
    {

      girinho();
      String sensores = ( String(bmp.readAltitude(1013.25),0) + '\t' + String(mpu6050.getAccX()) + '\t' + String(mpu6050.getAccY())+ '\t' + String(mpu6050.getAccZ()) + '\t' + String(horizontal) + '\t' + String(vertical) + '\t' + String(eixoz));
      String numero = (String(i) + '\t' ); 

      ant =(ant + '\n' + sensores);

      gravar(ant, "/leitura.txt");
      delay(100);
    }

    ledL();
    ant = (ant + '\n' + "----------------------------------------------");
    voo ++;
    gravar(String(voo),"/voos.txt");
    ler = 0;
    Serial.println("l.p");
  }
    
}
else //--- SOMENTE LEITURA
{
  //girinho();
  Serial.println(bmp.readAltitude(1013.25),0);
  //Serial.println(String(mpu6050.getAngleX()) + '\t' + String(mpu6050.getAngleY()) + '\t' + String(mpu6050.getAngleZ()));

}
}
//----------------------- sinais ---------------------------------//

void ledL() // led desliga
{
  digitalWrite(led,LOW);  
}

void ledH() // led liga
{
  digitalWrite(led,HIGH);  
}
*/
