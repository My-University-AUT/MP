#include <Arduino.h>

void setup()
{
  pinMode(40, OUTPUT);
}

void loop()
{
  digitalWrite(40, HIGH);
  delay(1000);

  digitalWrite(40, LOW);
  delay(1000);
}