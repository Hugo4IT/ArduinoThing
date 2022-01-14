unsigned char pixelData;

#define MCLK 45
#define PCLK 44

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
    pixelData |= digitalRead(46 + i) << i;
  }
}

void printData()
{
  Serial.print("Data: ");
  for (int i = 46; i < 54; i++)
  {
    Serial.print(digitalRead(i));
  }
  Serial.print(" | ");
  Serial.print(pixelData, BIN);
  Serial.println();
}

void loop()
{
  digitalWrite(MCLK, HIGH);
  if (digitalRead(44) > 0)
  {
    Serial.println("Received pixel clock signal");
    readPixelData();
    printData();
  }
  digitalWrite(MCLK, LOW);

  delay(3000);
}
