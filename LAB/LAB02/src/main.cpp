#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Keypad.h>

const int LED_PINS[9] = {8, 7, 6, 5, 4, 3, 2, 1, 0};
#define LED_NUM 9

const byte rows = 4; //four rows
const byte cols = 3; //three columns
char keys[rows][cols] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};
byte colPins[cols] = {49, 48, 47};     //connect to the column pinouts of the keypad
byte rowPins[rows] = {50, 51, 52, 53}; //connect to the row pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void turn_on_leds(int num_of_leds);
void first_part();
void second_part();

void setup()
{

  for (int i = 0; i < LED_NUM; i++)
  {
    pinMode(LED_PINS[i], OUTPUT);
  }

  Serial2.begin(9600);
}

void loop()
{

  // first_part();
  
  second_part();
}

void first_part()
{
  char key = keypad.getKey();

  if (key != NO_KEY)
  {
    Serial2.println(key);
    if (key != '*' && key != '#')
    {
      int number_of_led = ((int)key) - 48;
      turn_on_leds(number_of_led);
    }
  }
}

void second_part()
{
  // say what you got:
  Serial2.println("Enter number of LEDs");
  while (Serial2.available() == 0)
    ;

  String LEDs = Serial2.readString(); //Reading the Input string from Serial port.
  int num_of_leds = LEDs.toInt();

  if (num_of_leds > 0 && num_of_leds < 10)
  {
    turn_on_leds(num_of_leds);
  }
  else
  {
    Serial2.println("Invalid input!");
  }
}

void turn_on_leds(int num_of_leds)
{

  // first turn off all LEDs
  for (int i = 0; i < LED_NUM; i++)
  {
    digitalWrite(LED_PINS[i], LOW);
  }
  for (int i = 0; i < num_of_leds; i++)
  {
    digitalWrite(LED_PINS[i], HIGH);
  }
}