#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define ANCHO 128
#define ALTO 64
#define DOPPLER_PIN 4

Adafruit_SSD1306 display(ANCHO, ALTO, &Wire, -1);

float base = 2048;
float su = 0;
unsigned long ultimoLatido = 0;
int buf[3] = {0,0,0};
int idx = 0;

void setup(){
  Serial.begin(115200);
  Wire.begin(8, 9);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.println("Listo");
  display.display();
}

void loop(){
  int s = analogRead(DOPPLER_PIN);
  
  // 1. Quita la rampa que viste en el video
  base = base * 0.995 + s * 0.005;
  float f = s - base;
  
  // 2. Suaviza los picos dispersos
  su = su * 0.7 + f * 0.3;
  
  // Para ver en Plotter
  Serial.println(su + 100);

  // 3. Detecta solo si es pico grande y han pasado 600ms
  if(su > 15 && millis() - ultimoLatido > 600){
    unsigned long ahora = millis();
    unsigned long inter = ahora - ultimoLatido;

    if(inter > 400 && inter < 1500 && ultimoLatido != 0){
      buf[idx] = 60000 / inter;
      idx = (idx + 1) % 3;

      // Solo muestra cuando ya tiene 3 latidos para promediar
      if(buf[0] != 0 && buf[1] != 0 && buf[2] != 0){
        int bpm = (buf[0] + buf[1] + buf[2]) / 3;
        
        if(bpm > 50 && bpm < 200){
          display.clearDisplay();
          display.setTextSize(3);
          display.setCursor(15,5);
          display.print(bpm);
          display.setTextSize(2);
          display.setCursor(25,40);
          display.print("BPM");
          display.display();
        }
      }
    }
    ultimoLatido = ahora;
  }

  if(millis() - ultimoLatido > 3000){
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(10,25);
    display.print("Buscando...");
    display.display();
  }

  delay(15);
}
