#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESPAsyncWebServer.h>


const char* ssid = "De LANterfanters";
const char* password = "FlendedBamily#6";

ESP8266WebServer server(80);

// const char index_html[] PROGMEM = R"rawliteral(
// <!DOCTYPE HTML><html><head>
//   <title>ESP Input Form</title>
//   <meta name="viewport" content="width=device-width, initial-scale=1">
//   </head><body>
//   <form action="/get">
//     input1: <input type="text" name="input1">
//     <input type="submit" value="Submit">
//   </form><br>
//   <form action="/get">
//     input2: <input type="text" name="input2">
//     <input type="submit" value="Submit">
//   </form><br>
//   <form action="/get">
//     input3: <input type="text" name="input3">
//     <input type="submit" value="Submit">
//   </form>
// </body></html>)rawliteral";
String page = "";
double data;

void setup () {
    Serial.begin(115200);
    Serial.println();

    //WiFi.softAP("test", "arduinothing", 1, false, 1);
    WiFi.begin(ssid, password);
    Serial.print("Connecting...");

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    };

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    server.on("/", []() {
      page = "<h1>TEST</h1>";
      server.send(200, "text/html", page);
    });

    server.begin();
    Serial.println("Web server started!");
}

void loop() {
  Serial.println("Serial monitor is working");
  delay(2000);
  server.handleClient();
}