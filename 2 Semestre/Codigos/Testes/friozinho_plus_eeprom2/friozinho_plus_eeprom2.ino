#include <EEPROM.h>
#include <Thermistor.h>

const int numReadings = 201;
const unsigned long readingInterval = 900000; // Intervalo de 10 minutos em milissegundos

unsigned long previousMillis = 0;
int currentReading = 0;
bool recording = true;
double value1 = 0;
Thermistor temp(2);

void setup() {
  Serial.begin(9600);
  // Não é necessário alocar espaço na EEPROM explicitamente
  // A EEPROM da Arduino Nano possui 1024 bytes
  EEPROM.begin();
  Serial.print("ON");
  readAndPrintValues();
}

void loop() {
  unsigned long currentMillis = millis();

  if (recording && currentMillis - previousMillis >= readingInterval) {
    previousMillis = currentMillis;

    value1 = temp.getTemp();//

    Serial.print(sizeof(double));
    Serial.print(value1, 2);

    int addr1 = currentReading * (sizeof(double));

    EEPROM.put(addr1, value1);

    currentReading++;

    if (currentReading >= numReadings) {
      currentReading = 0;
      recording = false;
    }
    Serial.println("arquivo gravado");
  }

  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'R' || command == 'r') {
      readAndPrintValues();
    } else if (command == 'C' || command == 'c') {
      
      clearEEPROM();
    }
  }

}

void readAndPrintValues() {
  for (int i = 0; i < numReadings; i++) {
    int addr1 = i * (sizeof(double));

    double value1;
    EEPROM.get(addr1, value1);

    Serial.print("Reading ");
    Serial.print(i);
    Serial.print(": Value1 = ");
    Serial.println(value1, 2);

  }
}

void clearEEPROM() {
  for (int i = 0; i < numReadings; i++) {
    int addr1 = i * (sizeof(double));

    double value1 = 0.0;

    EEPROM.put(addr1, value1);
  }
  currentReading = 0;
  recording = true;
  Serial.println("EEPROM cleared and recording reset.");
}
