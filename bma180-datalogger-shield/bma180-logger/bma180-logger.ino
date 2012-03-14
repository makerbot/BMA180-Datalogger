#include <Wire.h>

int x;
int y;
int z;

void setup()
{
  Serial.begin(57600);
  initBMA180();
  Serial.println("MakerBot Industries Accelerometer Logger v1.0");
}

void loop()
{

  readAccel();

  delay(10);
}

