void setup(){
  Serial.begin(115200);
}
void loop(){
  int v = analogRead(3);
  Serial.println(v);
  delay(200);
}
