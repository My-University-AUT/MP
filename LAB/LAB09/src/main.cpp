#include <Arduino.h>
#include <Keypad.h>
#include <pitches.h>
#include <musics.h>

#define SOUND_PIN 8
#define ON_OFF_BTN 21

const byte rows = 4; // four rows
const byte cols = 3; // three columns
char keys[rows][cols] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'#', '0', '*'}};
byte rowPins[rows] = {4, 3, 2, 14}; // connect to the row pinouts of the keypad
byte colPins[cols] = {7, 6, 5};    // connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void play(int melody[], float durations[], int len);

void setup()
{
  pinMode(ON_OFF_BTN, INPUT_PULLUP);
}

void loop()
{
  char key = keypad.getKey();

  if (key != NO_KEY)
  {
    bool btn_is_off = digitalRead(ON_OFF_BTN); // button is pullup. so zero means button is pressed
    if (!btn_is_off)
    {
      switch (key)
      {
      case '1':
        play(melody, noteDurations, sizeof(melody) / sizeof(int));
        break;
      case '2':
        play(odeToJoy, odeToJoyDurations, sizeof(odeToJoy) / sizeof(int));
        break;
      case '3':
        play(jingleBells, jingleBellsDurations, sizeof(jingleBells) / sizeof(int));
        break;
      case '4':
        play(imperial_march, imperialMarchDurations, sizeof(imperial_march) / sizeof(int));
        break;
      }
    }
  }
}

void play(int melody[], float notDurations[], int len)
{
  for (int noteIndex = 0; noteIndex < len; noteIndex++)
  {
    float scale = analogRead(A15) / 512.0;
    Serial.println((int)12);
    int noteDuration = 1000 / notDurations[noteIndex];
    tone(SOUND_PIN, (int)(melody[noteIndex] * scale), noteDuration);

    int pauseBetweenNotes = noteDuration * 1.10;
    delay(pauseBetweenNotes);

    bool btn_is_off = digitalRead(ON_OFF_BTN); // button is pullup. so zero means button is pressed
    if (btn_is_off)
    {
      break;
    }
  }
}