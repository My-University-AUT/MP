#include <Arduino.h>
#include <Servo.h>
#include <Keypad.h>

const byte rows = 4; // four rows
const byte cols = 3; // three columns
char keys[rows][cols] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};
byte rowPins[rows] = {31, 32, 33, 34}; // connect to the row pinouts of the keypad
byte colPins[cols] = {29, 28, 27};     // connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

Servo servo;

void first_part(void);
void second_part(void);
void third_part(void);
void fourth_part(void);

void setup()
{
  // put your setup code here, to run once:
  servo.attach(9, 1000, 2000);

  Serial2.begin(9600);
}

void loop()
{
  // first_part();
  // second_part();
  // third_part();
  fourth_part();
}

// rotate between 0 to 90 and then 90 to 0
int degree = 90;
int step = 1;
void first_part(void)
{
  // map()

  servo.write(degree);
  Serial2.println(degree);
  degree += step;
  if (degree == 180 || degree == 90)
  {
    step = step * (-1);
  }

  delay(200);
}

// user enters number between 0 to 360 and it maps between -180 to 180
String entered_number = "";
void second_part(void)
{
  char key = keypad.getKey();
  if (key != NO_KEY)
  {
    Serial2.print(key);
    if (key == '#' || key == '*')
    {
      int number = entered_number.toInt();
      if (number >= 0 && number <= 360)
      {

        // int degreee = map(number, 0, 360, 0, 180);
        // simpler way :))
        int degreee = number / 2;
        Serial2.print("set to ");
        Serial2.println((degreee * 2) - 180);

        servo.write(degreee);
      }
      else
      {
        Serial2.print("Invalid number");
      }
      Serial2.println();
      entered_number = "";
    }
    else
    {
      entered_number += key;
    }
  }
}

int curr_degree = 0;
void third_part(void)
{
  while (Serial2.available() == 0)
    ;

  String enteredText = Serial2.readString();

  int number = enteredText.toInt();

  int degreee = (number * (-1)) + curr_degree;
  if (degreee >= -180 && degreee <= 180)
  {
    curr_degree = degreee;
    int degreee = map(curr_degree, -180, 180, 0, 180);
    // simpler way :))
    servo.write(degreee);
    Serial2.print("set to ");
    Serial2.println(curr_degree * -1);
  }
  else
  {
    Serial2.println("new degree is not between (-180 to 180)");
  }
}

void fourth_part(void)
{
  int p_value = analogRead(A0);            // reads the value of the potentiometer (value between 0 and 1023)
  p_value = map(p_value, 0, 1023, 0, 180); // scale it to use it with the servo (value between 0 and 180)

  Serial2.println("wrote to servo ");
  Serial2.println(p_value);

  servo.write(p_value);
  delay(1000);
}