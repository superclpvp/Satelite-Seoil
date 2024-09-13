#include <Arduino_KNN.h>
#include <SD.h>
#include <SPI.h>



const int INPUTS = 2;
const int CLASSES = 2;
const int K = 3;

KNNClassifier knn(INPUTS);

float pixel[2];

#define CS_PIN  10

void iniciarSD(){
  pinMode(CS_PIN, OUTPUT); // Declara pinoSS como saída
 
  if (SD.begin()) { // Inicializa o SD Card
    Serial.println("SD Card pronto para uso."); // Imprime na tela
  }
  else{
    Serial.println("ERRO NO SD");       
  }
}

void setup() {
  Serial.begin(9600);

  iniciarSD();  
  TreinarKnn();
  Analisar_Imagem_KNN(2);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void TreinarKnn(){
  
  String buffer_ler_linha = "";
  String buffer_ler_parte = "";
  int ultima_posicao = 0;
  int dado = 0;
  int X = 0;

  File arq_agua = SD.open("KnnAguaS.txt");
 
  Serial.println("Treinando KNN");
  bool loopAgua = true;      

  //Agua
  while(buffer_ler_linha != "fim"){
    //coluna 1
    arq_agua.seek(X);
    buffer_ler_linha = arq_agua.readStringUntil('\r');

    buffer_ler_parte = buffer_ler_linha.substring(0,buffer_ler_linha.indexOf('\t'));

    pixel[0] = (buffer_ler_parte.toFloat());
     

    buffer_ler_parte = buffer_ler_linha.substring(buffer_ler_linha.indexOf('\t'));
    
    pixel[1] = (buffer_ler_parte.toFloat());
        
    while (buffer_ler_linha != ""){
      X++;
      arq_agua.seek(X);
      buffer_ler_linha = arq_agua.readStringUntil('\r');
    }
    X+=2;
    arq_agua.seek(X);
    buffer_ler_linha = arq_agua.readStringUntil('\r');
    
      knn.addExample(pixel, 0);
      Serial.print(pixel[0], 3);  
      Serial.print(", ");
      Serial.println(pixel[1], 6);
    
  }

  arq_agua.close();
  File arq_oleo = SD.open("KnnOleoS.txt"); 
  Serial.println("Agua sucesso!");
  X = 0;
  buffer_ler_linha = "";
  while(buffer_ler_linha != "fim"){
    //coluna 1
    arq_oleo.seek(X);
    buffer_ler_linha = arq_oleo.readStringUntil('\r');

    buffer_ler_parte = buffer_ler_linha.substring(0,buffer_ler_linha.indexOf('\t'));

    pixel[0] = (buffer_ler_parte.toFloat());

    buffer_ler_parte = buffer_ler_linha.substring(buffer_ler_linha.indexOf('\t'));
    
    pixel[1] = (buffer_ler_parte.toFloat());
        
    while (buffer_ler_linha != ""){
      X++;
      arq_oleo.seek(X);
      buffer_ler_linha = arq_oleo.readStringUntil('\r');
    }
    X+=2;
    arq_oleo.seek(X);
    buffer_ler_linha = arq_oleo.readStringUntil('\r');
    
      knn.addExample(pixel, 1);
      Serial.print(pixel[0], 3);  
      Serial.print(", ");
      Serial.println(pixel[1], 6);
    
  }
  Serial.println("oleo sucesso!");  
}

void Analisar_Imagem_KNN(int EnderecoImagem){
  String NomeArquivo = "";
  String buffer_ler_linha = "";
  int local_Img = 0;
  float media;
  int N_vezes = 0;
  int X;
  float input[2];
  

  
  NomeArquivo = "I" + String(EnderecoImagem);
  
  File arq_Imagem = SD.open(NomeArquivo + ".txt"); 
  if(!arq_Imagem){
    Serial.println("erro ao ler arquivo de Imagem");
  } 
  else{
    Serial.println("Abriu"); 
  }


  while(buffer_ler_linha != "img"){
    X++;
    arq_Imagem.seek(X);
    buffer_ler_linha = arq_Imagem.readStringUntil('\r');
  }
  X+=2;
  local_Img = X;

  while(buffer_ler_linha != "fim"){
    N_vezes ++;
    if(!isnan(buffer_ler_linha.toFloat())){
      media += buffer_ler_linha.toFloat();
    }
    
    while (buffer_ler_linha != ""){
      X++;
      arq_Imagem.seek(X);
      buffer_ler_linha = arq_Imagem.readStringUntil('\t');
    }
    X++;   
    
    arq_Imagem.seek(X);
    buffer_ler_linha = arq_Imagem.readStringUntil('\t');    
  }
  X = local_Img;
  media /= N_vezes;
  input[0] = media;
  
  double Class_agua = 0;
  double Class_oleo = 0;
  int resultado;
  for(int x = 1; x <= N_vezes; x++){
    
    if(!isnan(buffer_ler_linha.toFloat())){
      input[1] = media - buffer_ler_linha.toFloat();

      resultado = knn.classify(input, K);

      if(resultado == 0){
        Class_agua ++;
      }
      else if (resultado == 1){
        Class_oleo ++;
      }
      
    }

    while (buffer_ler_linha != ""){
      X++;
      arq_Imagem.seek(X);
      buffer_ler_linha = arq_Imagem.readStringUntil('\t');
    }
    X++;   
    
    arq_Imagem.seek(X);
    buffer_ler_linha = arq_Imagem.readStringUntil('\t');       
    
  }
  Class_agua = (Class_agua / N_vezes)*100;
  Class_oleo = (Class_oleo / N_vezes)*100;
  Serial.print("agua - ");
  Serial.print(Class_agua);
  Serial.print("%");
  Serial.print(" oleo - ");
  Serial.print(Class_oleo);
  Serial.print("%");
}
