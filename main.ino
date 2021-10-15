#include <Servo.h>

Servo servo;

const int servoPort = 7;
int currentDirection = 0;

void setup() {

}

void loop() {
    servo.write(currentDirection++ % 180)
}