#include <SoftwareSerial.h>

int rxPin = 0;
int txPin = 1;

SoftwareSerial espSerial(rxPin, txPin);
int ledPin = 8;
bool ledState = false;

void setup() {
    Serial.begin(9600);
    espSerial.begin(9600);
    pinMode(ledPin, OUTPUT);
}

void loop() {
    if (espSerial.isListening()) {
        char data = espSerial.read();
        if (data == 'A') {
            // char bufferX = -1;
            // while (bufferX != -1) bufferX = espSerial.read();
            // char bufferY = -1;
            // while (bufferY != -1) bufferY = espSerial.read();
            // int x = bufferX - '0' - 1;
            // int y = bufferY - '0' - 1;
            while(!espSerial.available());
            char x = espSerial.read();
            int xCoord = x - '0' - 1;
            while(!espSerial.available());
            char y = espSerial.read();
            int yCoord = y - '0' - 1;
            if (xCoord == -1) {
                digitalWrite(ledPin, HIGH);
            }
            else if (xCoord == 0 || xCoord == 1) {
                digitalWrite(ledPin, LOW);
            }
            
            Serial.print("Received: [");
            Serial.print(xCoord);
            Serial.print(", ");
            Serial.print(yCoord);
            Serial.println("]");
        }
    }
    else {
    Serial.println("Loop completed without receiving serial Data");
    delay(10);
    }
}