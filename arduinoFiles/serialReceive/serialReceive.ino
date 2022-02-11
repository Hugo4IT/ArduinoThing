// #include <SoftwareSerial.h>

int rxPin = 0;
int txPin = 1;

// SoftwareSerial espSerial(rxPin, txPin);
int ledPin = 53;
bool ledState = false;

void setup() {
    Serial.begin(9600);
    // espSerial.begin(9600);
    pinMode(ledPin, OUTPUT);
}

void loop() {
    if (Serial.available()) {
        char data = Serial.read();
        if (data == 'A') {
            while(!Serial.available());
            int xCoord = Serial.read();
            int x = xCoord - 1;
            // int xCoord = x - '0' - 1;
            while(!Serial.available());
            int yCoord = Serial.read();
            int y = yCoord - 1;
            // int yCoord = y - '0' - 1;
            // if (xCoord == -1) {
            //     digitalWrite(ledPin, HIGH);
            // }
            // else if (xCoord == 0 || xCoord == 1) {
            //     digitalWrite(ledPin, LOW);
            // }
            
            Serial.print("Received: [");
            Serial.print(x);
            Serial.print(", ");
            Serial.print(y);
            Serial.println("]");
            digitalWrite(ledPin, HIGH * x);
        }
        else {
            Serial.println("Incorrect data");
        }
    }
    else {
      delay(10);
    //   Serial.println("EspSerial not listening");
    }
}
