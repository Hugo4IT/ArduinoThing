#include <SoftwareSerial.h>

int rxPin = 0;
int txPin = 1;


SoftwareSerial espSerial(rxPin, txPin);

void setup() {
    Serial.begin(9600);
    espSerial.begin(9600);
}

void loop() {
    int data = espSerial.read();
    Serial.print("Data received:");
    Serial.println(data);
    delay(1200);
}