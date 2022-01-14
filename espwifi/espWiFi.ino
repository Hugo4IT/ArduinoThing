#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


const char* ssid = "ESPWiFi";
const char* password = "arduinothing";

ESP8266WebServer server(80);

void setup () {
    Serial.begin(115200);
    Serial.println();

    WiFi.softAP("test", "arduinothing", 1, false, 1);

    Serial.print("Connecting...");

}

void loop() {
  Serial.println("Serial monitor is working");
  delay(2000);
}
