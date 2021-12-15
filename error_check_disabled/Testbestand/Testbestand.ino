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
  Serial.begin(9600);
  Serial.println();

  Serial.print("Scan networks:");
  Serial.println(WiFi.scanNetworks(false, false, 0U, (uint8*)"ArduinoTechnasium"));
  Serial.print("SSID:");
  Serial.println(WiFi.SSID());
  Serial.print("Hostname:");
  Serial.println(WiFi.getHostname());
  WiFi.begin("ArduinoTechnasium", "dinges1234");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop(){}
