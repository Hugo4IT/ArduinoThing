void setup() {
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    Serial.print("Arduino received: ");
    Serial.println((char)Serial.read());
  }
}
