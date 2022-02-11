// #include <SoftwareSerial.h>

// int rxPin = 0;
// int txPin = 1;

int dirA = 12;
int dirB = 13;
int speedA = 3;
int speedB = 11;
int brakeA = 9;
int brakeB = 8;

// SoftwareSerial espSerial(rxPin, txPin);
// int ledPin = 53;
// bool ledState = false;

void setup() {
    Serial.begin(9600);
    // espSerial.begin(9600);
    // pinMode(ledPin, OUTPUT);
    pinMode(dirA, OUTPUT);
    pinMode(dirB, OUTPUT);
    pinMode(speedA, OUTPUT);
    pinMode(speedB, OUTPUT);

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
            // digitalWrite(ledPin, HIGH * x);
            if (y == 1) {
                digitalWrite(dirA, LOW);
                digitalWrite(dirB, LOW);
                digitalWrite(brakeA, LOW);
                digitalWrite(brakeB, LOW);
                analogWrite(speedA, 255);
                analogWrite(speedB, 255);
            }
            else if (y == 0) {
                digitalWrite(dirA, LOW);
                digitalWrite(dirB, LOW);
                digitalWrite(brakeA, LOW);
                digitalWrite(brakeB, LOW);
                analogWrite(speedA, 0);
                analogWrite(speedB, 0);
            }
            else if (y == -1) {
                digitalWrite(dirA, HIGH);
                digitalWrite(dirB, HIGH);
                digitalWrite(brakeA, LOW);
                digitalWrite(brakeB, LOW);
                analogWrite(speedA, 255);
                analogWrite(speedB, 255);
            }
        }
        else {
            // Serial.println("Incorrect data");
        }
    }
    else {
      delay(10);
    //   Serial.println("EspSerial not listening");
    }
}
