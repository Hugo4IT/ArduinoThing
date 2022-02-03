#include <SoftwareSerial.h>

int rxPin = 1;
int txPin = 3;


SoftwareSerial ardSerial(rxPin, txPin);

void setup() {
    // Serial.begin(9600);
    ardSerial.begin(9600);
}

void loop() {
    for (int i = 0; i < 10; i++) {
        ardSerial.print(i);
        delay(1000);
    }
    
}