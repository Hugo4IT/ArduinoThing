#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.print("Setting up: ");
  if(WiFi.softAP("test", "ESP8266WIFI")) {
    Serial.println("Ready!");
  } else {
    Serial.println("Error!");
    
  }
}

void loop() {
  Serial.printf("Connected devices: %d\n", WiFi.softAPgetStationNum());
  delay(500);
}
