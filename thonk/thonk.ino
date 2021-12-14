unsigned char pixelData;

void setup()
{
  Serial.begin(115200);
  pinMode(44, INPUT);
  pinMode(45, OUTPUT);
  for (int i = 46; i < 53; i++)
  {
    pinMode(i, INPUT);
  }
}

void readPixelData()
{
  pixelData = 0;
  for (int i = 0; i < 8; i++)
  {
    pixelData |= digitalRead(46) << i;
  }
}

void printData()
{
  Serial.print("Data: ");
  for (int i = 46; i < 53; i++)
  {
    Serial.print(digitalRead(i));
  }
  Serial.print(" | ");
  Serial.print(pixelData);
  Serial.println();
}

void loop()
{
  digitalWrite(45, HIGH);
  if (digitalRead(44) > 0)
  {
    Serial.println("Received pixel clock signal");
    readPixelData();
    printData();
  }
  digitalWrite(45, LOW);

  delay(3000);
}
