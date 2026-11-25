// Código final - Filtro de latidos
const int pinDoppler = 34; // o A0 si usas Arduino
int base = 0;
long suma = 0;
int muestras = 0;
unsigned long ultimoLatido = 0;
int bpm = 0;

void setup() {
  Serial.begin(115200);
  // Calibra la base 3 segundos sin moverse
  for(int i=0;i<300;i++){
    suma += analogRead(pinDoppler);
    delay(10);
  }
  base = suma / 300;
  Serial.print("Base calibrada: ");
  Serial.println(base);
}

void loop() {
  int crudo = analogRead(pinDoppler);
  int filtrado = crudo - base;

  // Solo imprime la señal filtrada para el Plotter
  Serial.println(filtrado);

  // Detecta pico si es mayor a 15 y ya pasó 500ms del último (máx 120 BPM)
  if(abs(filtrado) > 15 && millis() - ultimoLatido > 500){
    ultimoLatido = millis();
    // Aquí podrías calcular BPM
  }
  delay(10);
}
