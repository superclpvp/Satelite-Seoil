void ProcessarImagem(int arquivo){
bool printar = false;
String Nome_arquivo = "Img" + String(arquivo);
int X = 0;
int LocalDaImagem;
bool acaba = false;
bool acaba2 = false;
bool acaba3 = false;
String a;
float maior_valor = 0;
float valor_atual = 0;

String endereco = "0";
String gpsX = "0";
String gpsY = "0";
String dia = "0";
String mes = "0";
String ano = "0";
String hora = "0";
String minuto = "0";

int tamanhoArquivo;

float Acumulador;
int VmaxLinha;
int VminLinha;
int MediaLinhas [24];
bool Blinha[24];
float MediaColuna [32];

int locimg = 0;
bool parte2 = false;
//================================================= parte 1 - Escala de cinza ===============================================//
  Serial.println("processando imagem...");
  Serial.println("1/3 Definindo escala de cinza");

   File ImagemAntes = SD.open(Nome_arquivo + ".txt");
   
if(ImagemAntes){   
    SD.remove("tempIMG.txt");
    if (printar){Serial.println(ImagemAntes.size());}
    tamanhoArquivo = ImagemAntes.size();
    X = 0; 
    ImagemAntes.seek(X);
  
    endereco = ImagemAntes.readStringUntil('\r');
    while (a != ""){
       X++;
       ImagemAntes.seek(X);
       a = ImagemAntes.readStringUntil('\r');
    }
    X+=2;
    gpsX = ImagemAntes.readStringUntil('\r');
    
    while (a != ""){
       X++;
       ImagemAntes.seek(X);
       a = ImagemAntes.readStringUntil('\r');
    }
    X+=2;
    gpsY = ImagemAntes.readStringUntil('\r');
    
    while (a != ""){
       X++;
       ImagemAntes.seek(X);
       a = ImagemAntes.readStringUntil('\r');
    }
    X+=2;

    dia = ImagemAntes.readStringUntil('\r');
    while (a != ""){
       X++;
       ImagemAntes.seek(X);
       a = ImagemAntes.readStringUntil('\r');
    }
    X+=2;
    
    mes = ImagemAntes.readStringUntil('\r');
    while (a != ""){
       X++;
       ImagemAntes.seek(X);
       a = ImagemAntes.readStringUntil('\r');
    }
    X+=2;

    ano = ImagemAntes.readStringUntil('\r');
    while (a != ""){
       X++;
       ImagemAntes.seek(X);
       a = ImagemAntes.readStringUntil('\r');
    }
    X+=2;

    hora = ImagemAntes.readStringUntil('\r');
    while (a != ""){
       X++;
       ImagemAntes.seek(X);
       a = ImagemAntes.readStringUntil('\r');
    }
    X+=2;

    minuto = ImagemAntes.readStringUntil('\r');
    while (a != ""){
       X++;
       ImagemAntes.seek(X);
       a = ImagemAntes.readStringUntil('\r');
    }
    X+=2;
    
    if (printar){
    Serial.print(endereco);
    Serial.print(gpsX);
    Serial.println(gpsY);
    }
  
    X = 0; 
    while (acaba == false){
  //    delay(10);
      ImagemAntes.seek(X);
      a = ImagemAntes.readStringUntil('\r');
      
      if (printar){
      Serial.println(a);
      Serial.println(X);
      }
      //PROCURAR Imagem
      if (a == "img"){
         while (a != ""){
            X++;
            ImagemAntes.seek(X);
            a = ImagemAntes.readStringUntil('\r');
         }
         X++;
        LocalDaImagem = X;  
        ImagemAntes.seek(X);
        a = ImagemAntes.readStringUntil('\t');
        valor_atual = a.toFloat();
        if (printar){Serial.println(maior_valor);}
        
         while (acaba2 == false){
          
             for(int u = 1; u <= 768; u++){// definir o maior valor da imagem
               ImagemAntes.seek(X);
               a = ImagemAntes.readStringUntil('\t');              
               valor_atual = a.toFloat();     
               if (printar){
               Serial.print(u);
               Serial.print(" ");
               Serial.println(maior_valor);
               }
               while (a != ""){
                  X++;
                  ImagemAntes.seek(X);
                  a = ImagemAntes.readStringUntil('\t');
               }
              if(valor_atual > maior_valor){
                maior_valor = valor_atual;
              }
                X++;
            }
            
            acaba2 = true;
            acaba = true;
            X = 0;
         }
      }
      else{
        X++;  
      }
      
    }  
  
    Saveln("tempIMG",endereco);
    Saveln("tempIMG",gpsX);  
    Saveln("tempIMG",gpsY);
    Saveln("tempIMG",dia);
    Saveln("tempIMG",mes);  
    Saveln("tempIMG",ano);
    Saveln("tempIMG",hora);
    Saveln("tempIMG",minuto);  
    
    Saveln("tempIMG","");
    Saveln("tempIMG","img");
  
    X = LocalDaImagem;
  
  
  
    for(int y = 1; y <= 768; y++){
  //    delay(10);
      ImagemAntes.seek(X);
      a = ImagemAntes.readStringUntil('\t');
    
       
      valor_atual = a.toFloat();        
      valor_atual = valor_atual/maior_valor;
  
      if (printar){
        Serial.print(y);
        Serial.print(" ");
        Serial.println(valor_atual);
      }
      Save("tempIMG",String(valor_atual));
      Save("tempIMG","\t");
  
      
      while (a != ""){
         X++;
         ImagemAntes.seek(X);
         a = ImagemAntes.readStringUntil('\t');
      }
      X++;
    }
    ImagemAntes.close();
  
//====================================== parte 2 - media das linhas e colunas ==============================================//
  Serial.println("2/3 - definindo media das linhas e colunas");
  
  
    X = 0;
    
    File ProcessandoImg = SD.open("tempIMG.txt");
  
    while (parte2 == false){
      ProcessandoImg.seek(X);
      a = ProcessandoImg.readStringUntil('\r');
      
      if (printar){
        Serial.println(a);
        Serial.println(X);
      }
      //PROCURAR Imagem
      if (a == "img"){
         while (a != ""){
           X++;
           ProcessandoImg.seek(X);
           a = ProcessandoImg.readStringUntil('\r');
         }
         X++;
         locimg = X;
         //linha
        for(int x = 1 ; x <= 24; x++){
  //        delay(100);
          for(int y = 1; y <= 32; y++){
  //          delay(10);
            ProcessandoImg.seek(X);
            a = ProcessandoImg.readStringUntil('\t');
  
            valor_atual = a.toFloat();
  
            if(!isnan(valor_atual)){
              Acumulador = valor_atual + Acumulador ;
            }
            //Serial.println(valor_atual);
  
            while (a != ""){
               X++;
               ProcessandoImg.seek(X);
               a = ProcessandoImg.readStringUntil('\t');
            }
            X++;
          }  
          MediaLinhas[x] = (Acumulador / 32) * 1000;
          if (printar){Serial.println(MediaLinhas[x]);}
          Acumulador = 0;
          
        }
  
  //      while(isnan(VmaxLinha) or VmaxLinha <= 0 && isnan(VminLinha) or VminLinha <= 0){

          for(int repetir = 0; repetir <= 3; repetir++){
            for (int x = 1; x < 24; x++) {
                VmaxLinha += MediaLinhas[x];
                if (printar){Serial.println("vmax " + String(VmaxLinha));}
            }
            VmaxLinha = VmaxLinha / 24;
            
            if (printar){Serial.println("vmax media " + String(VmaxLinha));}
            
            float desvMed = 0.0;
          
            for(int i = 0; i < 24; ++i) {
  //            delay(10);
              desvMed += abs(MediaLinhas[i] - VmaxLinha);
              if (printar){Serial.println("desvMed " + String(desvMed));}
            }
            desvMed /= 24;
            if (printar){Serial.println("desvMed final " + String(desvMed));}
            VminLinha = VmaxLinha - desvMed ;
          }
  //      }
        if (printar){
        Serial.print(" Vmax: ");
        Serial.print(VmaxLinha);      
        Serial.print(" Vmin: ");
        Serial.println(VminLinha);
        Serial.println("fim");
        }
  
  
        for (int x = 1; x < 24; x++) {
          if(MediaLinhas[x] < VmaxLinha && MediaLinhas[x] > VminLinha){
            Blinha[x] = true;
            if (printar){Serial.println(MediaLinhas[x]);}
          }
          else{
            Blinha[x] = false;  
          }
        }
        if (printar){
        Serial.print(" Vmin: ");
        Serial.println(VminLinha);
        }
        parte2 = true;
      }
      else{
        X++;
      }    
    }
    
//==================================parte 3 - final ("cortar" e salvar a imagem)==========================================//
    Serial.println("3/3 - recortando imagem");
    ProcessandoImg.close();
  
    String NomeArquivo = "I" + endereco;
    while (!SD.exists(NomeArquivo + ".txt")){
       File Datafile = SD.open(NomeArquivo + ".txt", FILE_WRITE);
       Datafile.close();
       if (printar){Serial.print("criando arquivo");}
    }
      
    Saveln(NomeArquivo,endereco);
    Saveln(NomeArquivo,gpsX);  
    Saveln(NomeArquivo,gpsY);
    Saveln(NomeArquivo,dia);
    Saveln(NomeArquivo,mes);  
    Saveln(NomeArquivo,ano);
    Saveln(NomeArquivo,hora);
    Saveln(NomeArquivo,minuto);  
    Saveln(NomeArquivo,"");
    Saveln(NomeArquivo,"img"); 
    
    File CopyImage = SD.open("tempIMG.txt");
    
    X = locimg;
  
    for(int x = 1; x <= 24; x++){
    for(int y = 1; y <= 32; y++){
  //    delay(10);
      CopyImage.seek(X);
      a = CopyImage.readStringUntil('\t');
       
      valor_atual = a.toFloat();   
           
      if(MediaLinhas[x] < VmaxLinha && MediaLinhas[x] > VminLinha){
  //      delay(1);
        if (printar){
        Serial.print(x);
        Serial.print(" ");
        Serial.print(y);
        Serial.print(" ");
        Serial.println(valor_atual);
        }
        Save(NomeArquivo,String(valor_atual));
        Save(NomeArquivo,"\t");
      }
      
      while (a != ""){
         X++;
         CopyImage.seek(X);
         a = CopyImage.readStringUntil('\t');
      }
      X++;
    }
    }
    Save(NomeArquivo,"fim");
    Save(NomeArquivo,"\t");
    
    CopyImage.close();
    SD.remove("tempIMG.txt");
    Serial.print("imagem processada com sucesso!");
  }
  else{
     Serial.println("erro ao abrir o arquivo");
    
  }
  subManager("M1ImgsNProcss");
  addManager("M2ImgsProcss", endereco.toInt());
}
