// Código para ESP32 + TP-2023
const int pinECG = 32;  // si no te jala prueba con 33 o 35

void setup() {
  Serial.begin(9600);
  analogReadResolution(12); // ESP32 es 12 bits
}

void loop() {
  int valor = analogRead(pinECG);
  Serial.println(valor);
  delay(20);
}
