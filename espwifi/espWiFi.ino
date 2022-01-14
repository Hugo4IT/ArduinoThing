#include <ESP8266WiFi.h>
<<<<<<< HEAD
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


const char* ssid = "ESPWiFi";
const char* password = "arduinothing";

ESP8266WebServer server(80);
=======

const char* ssid = "iPhone van David";
const char* password = "ProtonVPN";
>>>>>>> 9d5cefb38ace9f9e022280f781f830159fd9b627

void setup () {
    Serial.begin(115200);
    Serial.println();

<<<<<<< HEAD
    WiFi.softAP("test", "arduinothing", 1, false, 1);

=======
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    
>>>>>>> 9d5cefb38ace9f9e022280f781f830159fd9b627
    Serial.print("Connecting...");
}

<<<<<<< HEAD
}

void loop() {
  Serial.println("Serial monitor is working");
  delay(2000);
}
=======
void loop() {
    Serial.print("IpAddress: ");
    Serial.println(WiFi.localIP());
    delay(2000);
}
>>>>>>> 9d5cefb38ace9f9e022280f781f830159fd9b627
