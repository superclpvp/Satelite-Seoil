void setup() {
  Serial.begin(9600);

  pinMode(02, INPUT);
}

void loop() {
  Serial.print(digitalRead(02));
}
