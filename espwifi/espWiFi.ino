#include <ESP8266WiFi.h>

const char* ssid = "iPhone van David";
const char* password = "ProtonVPN";

void setup () {
    Serial.begin(115200);
    Serial.println();

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    
    Serial.print("Connecting...");
}

void loop() {
    Serial.print("IpAddress: ");
    Serial.println(WiFi.localIP());
    delay(2000);
}