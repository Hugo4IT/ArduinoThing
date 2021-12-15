#include <Servo.h>

Servo myservo;

int pos = 0;
int servoPin = 7;
int potPin = A0;
int potVal = 0;

void setup() {
  myservo.attach(7);
  pinMode(potPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  potVal = analogRead(potPin);
  Serial.println(potVal);
  pos = potVal*(180./1023.);
  myservo.write(pos);
}