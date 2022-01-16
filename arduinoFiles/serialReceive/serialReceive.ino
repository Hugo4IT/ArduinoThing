#include <SoftwareSerial.h>

int rxPin = 0;
int txPin = 1;

char receivedChars[4];
bool newData = false;


SoftwareSerial espSerial(rxPin, txPin);
int ledPin = 8;

void setup() {
    Serial.begin(9600);
    espSerial.begin(9600);

}

void loop() {
    if (espSerial.isListening()) {
        int data = espSerial.read();
        if (data != -1){
            
            Serial.println(data);
        }
        // else {
        //     Serial.print('.');
        //     delay(100);
        // }
        
         
        // int i = 0;
        // while (data != -1 && newData == false) {
        //     receivedChars[i] = data;

        // }
        // if (data != -1) {
        //     Serial.print("Data: ");
        //     Serial.println(data);
        // }
        
        
        // ALTERNATIVE READING SCRIPT
        // Serial.println("Arduino is listening!");
        // Serial.print("Data recieved: ");
        // int data = espSerial.read();
        // Serial.println(data);
        // delay(5);

        // DECODING STUFF
        // unsigned char *payload = espSerial.read();
        // for (int i = 0; i < 5; i++) {
        //     Serial.print(payload[i]);
        // }
        // if (payload[0] == 'A') { // Axis, format: "A[+/-]X[+/-]Y", e.g.: A-1+1 for X:-1 and Y:1
        //     int x = (int)((char)payload[2] - '0');
        //     int y = (int)((char)payload[4] - '0');
        //     if (payload[1] == '-') x *= -1;
        //     if (payload[3] == '-') y *= -1;
        //     Serial.print("X: ");
        //     Serial.print(x);
        //     Serial.print(" Y: ");
        //     Serial.println(y);
        //     if (x != 0 || y !=0)
        //     {
        //         digitalWrite(ledPin, HIGH);
        //         delay(2000);
        //     }
            
        // }
        // else {
        //     Serial.println("Data not recieved (in the right format)");
        // }
    }
    else {
    Serial.println("Loop completed without receiving serial Data");
    delay(10);
    }
}