int pin = 3;
float base = 0;

void setup() {
  Serial.begin(115200);
  // Calibra 3 segundos quieto
  Serial.println("Calibrando... no te muevas");
  long suma = 0;
  for(int i=0; i<300; i++){ suma += analogRead(pin); delay(10); }
  base = suma / 300.0;
  Serial.print("Base lista: "); Serial.println(base);
}

void loop() {
  int raw = analogRead(pin);
  
  // Filtro: le quitamos la base para dejar solo el movimiento chiquito
  float filtrado = raw - base;
  
  // Se adapta despacito a la base
  base = base * 0.995 + raw * 0.005;

  Serial.print(raw);
  Serial.print(",");
  Serial.println(filtrado);

  // Si el movimiento chiquito es más grande que 15, es latido / respiración
  if(abs(filtrado) > 20){
    Serial.println(">>> LATIDO / MOVIMIENTO <<<");
  }

  delay(30); // 30ms = más rápido para agarrar el corazón
}
