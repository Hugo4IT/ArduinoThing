#include <ESP8266WiFi.h>

/* A Direction, PWM and Brake */
#define A_DIR 12
#define A_PWM 3
#define A_BRK 9

/* B Direction, PWM and Brake */
#define B_DIR 13
#define B_PWM 11
#define B_BRK 8

/*
 * {A|B}_DIR - Digital, HIGH = Clockwise, LOW = CounterClockwise
 * {A|B}_PWM - Analog, controls speed
 * {A|B}_BRK - Digital, HIGH = Stop motors, LOW = Nothing
 */

void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.scanNetworks
  WiFi.begin("ArduinoESPTest", "dinges1234");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(B_DIR, OUTPUT);
  pinMode(B_PWM, OUTPUT);
  pinMode(B_BRK, OUTPUT);
}

void stopMotors() {
  digitalWrite(B_BRK, HIGH);
  analogWrite(B_PWM, 0);
  delay(50);
  digitalWrite(B_BRK, LOW);
}

void loop() {
  digitalWrite(B_BRK, LOW);
  digitalWrite(B_DIR, HIGH);
  analogWrite(B_PWM, 500);
}
