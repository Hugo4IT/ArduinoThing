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

    //Set pinmodes for motor shield
    pinMode(dirA, OUTPUT);
    pinMode(dirB, OUTPUT);
    pinMode(speedA, OUTPUT);
    pinMode(speedB, OUTPUT);
    
    //Disable brakes
    digitalWrite(brakeA, LOW);
    digitalWrite(brakeB, LOW);

}

void left(bool dir, int speed) {
    if (dir) {dir = HIGH;}
    else if (!dir) {dir = LOW;}
    digitalWrite(dirA, dir);
    digitalWrite(speedA, speed);
}

void right(bool dir, int speed) {
    if (dir) {dir = HIGH;}
    else if (!dir) {dir = LOW;}
    digitalWrite(dirB, dir);
    digitalWrite(speedB, speed);
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
            // if (y == 1) {
            //     digitalWrite(dirA, LOW);
            //     digitalWrite(dirB, LOW);
            //     digitalWrite(brakeA, LOW);
            //     digitalWrite(brakeB, LOW);
            //     analogWrite(speedA, 255);
            //     analogWrite(speedB, 255);
            // }
            // else if (y == 0) {
            //     digitalWrite(dirA, LOW);
            //     digitalWrite(dirB, LOW);
            //     digitalWrite(brakeA, LOW);
            //     digitalWrite(brakeB, LOW);
            //     analogWrite(speedA, 0);
            //     analogWrite(speedB, 0);
            // }
            // else if (y == -1) {
            //     digitalWrite(dirA, HIGH);
            //     digitalWrite(dirB, HIGH);
            //     digitalWrite(brakeA, LOW);
            //     digitalWrite(brakeB, LOW);
            //     analogWrite(speedA, 255);
            //     analogWrite(speedB, 255);
            // }
            
            // //motorA is left, motorB is right
            // //Forward and Backwards
            // if (y == 1 && x == 0) {motorA(true, 255); motorB(true, 255);}
            // else if (y == -1 && x == 0) {motorA(false, 255); motorB(false, 255);}

            // //Left and Right stationary turning
            // if (y == 0 && x == -1) {motorA(false, 255); motorB(true, 255);}
            // else if (y == 0 && x == 1) {motorA(true, 255); motorB(false, 255);}

            if (y == 1) {
                if (x == -1) {left(true, 127); right(true, 255);}        //Left forward turn
                else if (x == 0) {left(true, 255); right(true, 255);}    //Forward
                else if (x == 1) {left(true, 255); right(true, 127);}    //Right turn
            }
            else if (y == 0) {
                if (x == -1) {left(false, 255); right(true, 255);}       //Stationary left
                else if (x == 0) {left(true, 0); right(true, 0);}        //Stationary
                else if (x == 1) {left(true, 255); right(false, 255);}   //Stationary right
            }
            else if (y == -1) {
                if (x == -1) {left(false, 127); right(false, 255);}      //Left backwards turn
                else if (x == 0) {left(false, 255); right(false, 255);}  //Backwards
                else if (x == 1) {left(false, 255); right(false, 127);}  //Right backwards turn
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
