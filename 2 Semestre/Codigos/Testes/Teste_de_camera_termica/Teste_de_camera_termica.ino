#include <Wire.h>

#include <MLX90640_API.h>
#include <MLX90640_I2C_Driver.h>


const int MLX90640_address = 0x33;

float mlx90640To[768];
paramsMLX90640 mlx90640;

#define TA_SHIFT 8 //Default shift for MLX90640 in open air

void setup() {
  Wire.begin();
  Wire.setClock(400000); //deixar o clock do wire para 400kHz

  Serial.begin(115200);
  
  Iniciar_Cam();
}

void loop() {
  print_Cam();
  delay(100000);
}


void print_Cam(){
  
  long startTime = millis();
  for (byte x = 0 ; x < 2 ; x++)
  {
    uint16_t mlx90640Frame[834];
    int status = MLX90640_GetFrameData(MLX90640_address, mlx90640Frame);

    float vdd = MLX90640_GetVdd(mlx90640Frame, &mlx90640);
    float Ta = MLX90640_GetTa(mlx90640Frame, &mlx90640);

    float tr = Ta - TA_SHIFT; //Reflected temperature based on the sensor ambient temperature
    float emissivity = 0.95;

    MLX90640_CalculateTo(mlx90640Frame, &mlx90640, emissivity, tr, mlx90640To);
  }
  long stopTime = millis();

  for (int x = 0 ; x < 768 ; x++)
  {
    //if(x % 8 == 0) Serial.println();
    Serial.print(mlx90640To[x], 2);
    Serial.print(",");
  }
  Serial.println("");
  
}
void Iniciar_Cam(){
  Wire.beginTransmission((uint8_t)MLX90640_address);
  
  int status;
  uint16_t eeMLX90640[832];
  status = MLX90640_DumpEE(MLX90640_address, eeMLX90640);

  if (status != 0)
    Serial.println("falha no carregamento dos parametros do sistema");
    
  status = MLX90640_ExtractParameters(eeMLX90640, &mlx90640);

  if (status != 0)
    Serial.println("falha em extrair o parametrp");

  //MLX90640_SetRefreshRate(MLX90640_address, 0x02); //Set rate to 2Hz
  MLX90640_SetRefreshRate(MLX90640_address, 0x03); //Set rate to 4Hz
  //MLX90640_SetRefreshRate(MLX90640_address, 0x07); //Set rate to 64Hz  
  
  
}
