#include <Servo.h>

Servo myservo;

void setup() {
    // myservo.attach(8);
    // myservo.write(90);
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    digitalWrite(0, HIGH);
    digitalWrite(1, HIGH);
}

void loop() {
    // put your main code here, to run repeatedly:
    
    digitalWrite(8, HIGH);
    delay(2000);
    digitalWrite(8, LOW);
    delay(2000);
}