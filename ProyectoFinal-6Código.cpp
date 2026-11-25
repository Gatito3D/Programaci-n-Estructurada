#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define ANCHO 128
#define ALTO 64
#define DOPPLER_PIN 4

Adafruit_SSD1306 display(ANCHO, ALTO, &Wire, -1);

int bpm = 0;
unsigned long ultimoLatido = 0;

void setup(){
  Serial.begin(115200);
  Wire.begin(8, 9);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED no encontrado");
  }
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.println("Listo");
  display.display();
}

void loop(){
  int s = analogRead(DOPPLER_PIN);
  
  static float f = 2048;
  f = f*0.9 + s*0.1;

  Serial.println(f); // para ver en el Plotter

  // Umbral corregido a 1850 como viste en tu video
  if(f > 1850 && millis() - ultimoLatido > 400){
    unsigned long ahora = millis();
    unsigned long inter = ahora - ultimoLatido;
    
    if(inter > 350 && inter < 1500){
      bpm = 60000 / inter;
      
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
      ultimoLatido = ahora;
    } else if (ultimoLatido == 0){
      ultimoLatido = ahora;
    }
  }

  if(millis() - ultimoLatido > 3000 && bpm != 0){
    bpm = 0;
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(10,25);
    display.print("Buscando...");
    display.display();
  }
  
  delay(15);
}
