#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SDA_PIN 9
#define SCL_PIN 8
#define ANCHO 128
#define ALTO 64
#define DIRECCION 0x3C

Adafruit_SSD1306 display(ANCHO, ALTO, &Wire, -1);

void setup(){
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.begin(115200);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, DIRECCION)){
    Serial.println("No prendio la OLED");
    while(1);
  }
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("YA JALO!");
  
  display.setTextSize(1);
  display.setCursor(0, 40);
  display.println("0x3C en 9,8");
  
  display.display();
  Serial.println("YA JALO en pantalla!");
}

void loop(){
}
