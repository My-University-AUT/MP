#include <Arduino.h>
#include <LowPower.h>
#include "Queue.h"

#define interruptPin_1 18
#define interruptPin_2 19
#define interruptPin_3 20
// const  Queue  q;
const int LED_PINS[8] = {0, 1, 2, 3, 4, 5, 6, 7};

Queue<int> q = Queue<int>(10);

#define MY_NAME "ALI"

void off_();
void all_on_();
void blink_();

void setup()
{

  pinMode(interruptPin_1, INPUT);
  pinMode(interruptPin_2, INPUT);
  pinMode(interruptPin_3, INPUT);

  attachInterrupt(digitalPinToInterrupt(interruptPin_1), all_on_, FALLING);
  attachInterrupt(digitalPinToInterrupt(interruptPin_2), blink_, FALLING);
  attachInterrupt(digitalPinToInterrupt(interruptPin_3), off_, FALLING);

  // for (int i = 0; i < sizeof(LED_PINS); i++)
  for (int i = 0; i < 8; i++)
  {
    pinMode(LED_PINS[i], OUTPUT);
  }
}

void loop()
{

  int state = q.pop();
  if (state)
  {
    if (state == 1)
    {
      const int name_len = strlen(MY_NAME);
      for (int j = 0; j < name_len; j++)
      {
        for (int i = 0; i < 8; i++)
        {
          digitalWrite(LED_PINS[i], HIGH);
        }
        delay(300);

        for (int i = 0; i < 8; i++)
        {
          digitalWrite(LED_PINS[i], LOW);
        }
        delay(00);
      }
      for (int i = 0; i < 8; i++)
      {
        digitalWrite(LED_PINS[i], HIGH);
      }
    }
    else if (state == 2)
    {
      for (int i = 0; i < 8; i++)
      {
        digitalWrite(LED_PINS[i], HIGH);
        delay(300);
      }
    }
    else if (state == 3)
    {
      for (int i = 0; i < 8; i++)
      {
        digitalWrite(LED_PINS[i], LOW);
      }
    }
  }
}

void blink_()
{
  q.push(1);
}

void all_on_()
{
  q.push(2);
}

void off_()
{
  q.push(3);
}
