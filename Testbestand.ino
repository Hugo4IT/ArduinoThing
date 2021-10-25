#include <Servo.h>

Servo myServo;

int ServoPin = 7;
int ServoPos = 180;

void setup() {
  myServo.attach(ServoPin);
}

void loop() {
  myServo.write(180);
  delay(500);
  myServo.write(0);
  delay(500);
}

//DIT IS EEN TESTCOMMENT