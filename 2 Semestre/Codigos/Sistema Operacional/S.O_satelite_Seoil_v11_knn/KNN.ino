void Treinar_KNN(){
  float placeHolderTRAINING = 1;

  for (int currentClass = 0; currentClass < Classes; currentClass++) {

      for (int currentExample = 0; currentExample < Imagens_Treino; currentExample++) {

        //myKNN.addExample(placeHolderTRAINING, currentClass);
  
      }
  }  
}

String Analizar_Imagem(String arquivo){
   bool AGUA;
   float IMAGEM_DO_ARQUIVO = 1;

   //float classification = myKNN.classify(IMAGEM_DO_ARQUIVO, K);

   //if (classification == 1) {AGUA == true;} else{ AGUA == false;}
   if(AGUA == true){
    return("Agua");
   }
   else{
    return("oleo");
   }
}
