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

// void left(bool dir, int speed) {
//     int dir = dir ? HIGH : LOW;
//     digitalWrite(dirA, dir);
//     digitalWrite(speedA, speed);
// }

// void right(bool dir, int speed) {
//     int dir = dir ? HIGH : LOW;
//     digitalWrite(dirB, dir);
//     digitalWrite(speedB, speed);
// }

enum Direction {
    FORWARDS = HIGH,
    BACKWARDS = LOW
};

enum Speed {
    NONE = 0,
    HALF = 127,
    FULL = 255
};

typedef struct Instruction{
    struct {
        int direction;
        unsigned char speed;
    } left;
    struct {
        int direction;
        unsigned char speed;
    } right;
} Instruction;

const Instruction instructions[3][3] = {
    //      Left               Right       |       Left               Right        |       Left              Right
    // Dir        Speed | Dir       Speed  |  Dir        Speed | Dir        Speed  |  Dir       Speed | Dir        Speed
    {{{FORWARDS,  HALF}, {FORWARDS, FULL}}, {{FORWARDS,  FULL}, {FORWARDS,  FULL}}, {{FORWARDS, HALF}, {FORWARDS,  FULL}}},
    {{{BACKWARDS, FULL}, {FORWARDS, FULL}}, {{FORWARDS,  NONE}, {FORWARDS,  NONE}}, {{FORWARDS, FULL}, {BACKWARDS, FULL}}},
    {{{BACKWARDS,  HALF}, {BACKWARDS, FULL}}, {{BACKWARDS, FULL}, {BACKWARDS, FULL}}, {{BACKWARDS, FULL}, {BACKWARDS,  HALF}}}
};

struct Instruction getInstruction(int x, int y) {
    return instructions[-y + 1][x + 1];
}

void input(int x, int y) {
    Instruction inst = getInstruction(x, y);
    digitalWrite(dirA, inst.left.direction);
    digitalWrite(speedA, inst.left.speed);
    digitalWrite(dirB, inst.right.direction);
    digitalWrite(speedB, inst.right.speed);
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

            input(x, y);

            // Serial.print("Received: [");
            // Serial.print(x);
            // Serial.print(", ");
            // Serial.print(y);
            // Serial.println("]");

            // if (y == 1) {
            //     if (x == -1) {left(true, 127); right(true, 255);}        //Left forward turn
            //     else if (x == 0) {left(true, 255); right(true, 255);}    //Forward
            //     else if (x == 1) {left(true, 255); right(true, 127);}    //Right turn
            // }
            // else if (y == 0) {
            //     if (x == -1) {left(false, 255); right(true, 255);}       //Stationary left
            //     else if (x == 0) {left(true, 0); right(true, 0);}        //Stationary
            //     else if (x == 1) {left(true, 255); right(false, 255);}   //Stationary right
            // }
            // else if (y == -1) {
            //     if (x == -1) {left(false, 127); right(false, 255);}      //Left backwards turn
            //     else if (x == 0) {left(false, 255); right(false, 255);}  //Backwards
            //     else if (x == 1) {left(false, 255); right(false, 127);}  //Right backwards turn
            // }
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
