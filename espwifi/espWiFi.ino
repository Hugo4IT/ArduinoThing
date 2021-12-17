#include <ESP8266Wifi.h>

void setup () {
    Serial.begin(115200);
    Serial.println();

    WiFi.softAP("test", "arduinothing", 1, false, 1)

    Serial.print("Connecting...");

}