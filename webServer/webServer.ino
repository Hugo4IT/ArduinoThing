#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

// Weird hack to include file as string
const String PAGE =
#include "webPage.html"
;
const String HEADERS = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

WiFiServer server(80);
WebSocketsServer webSocket(81);

const char SSID[] = "ESP_SERV";
const char PASS[] = "pain";

void setup() {
    Serial.begin(115200);
    Serial.print("Creating AP... ");
    if (WiFi.softAP(SSID, PASS)) {
        Serial.println("Done!");
    } else {
        Serial.println("Failed.");
        Serial.println("The Arduino will now start looping to prevent further code execution.");
        Serial.println("To retry, press the RESET button on the Arduino.");
        while(1);
    }

    Serial.print("Starting WebServer... ");
    server.begin();
    Serial.println("Done!");

    Serial.print("Starting WebSocketsServer... ");
    webSocket.begin();
    webSocket.onEvent();
    Serial.println("Done!");
}

void loop() {
    webSocket.loop();

    WiFiClient client = server.available();
    if (!client) return;

    client.flush();
    client.print(HEADERS);
    client.print(PAGE);
    Serial.println("Page was requested, and sent.");

    delay(5);
}

void webServerEvent(char num, WStype_t type, unsigned char *payload, size_t length) {
    if (type == WStype_TEXT) {
        if (payload[0] == 'A') { // Axis, format: "A[+/-]X[+/-]Y", e.g.: A-1+1 for X:-1 and Y:1
            int x = (int)((char)payload[2] - '0');
            int y = (int)((char)payload[4] - '0');
            if (payload[1] == '-') x *= -1;
            if (payload[3] == '-') y *= -1;
            Serial.printf("Recieved: [%d, %d]\n", x, y);
        }
    }
}