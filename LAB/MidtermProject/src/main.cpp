#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

#define MAX_ATTEMPTS 3

const byte rows = 4; // four rows
const byte cols = 3; // three columns
char keys[rows][cols] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'#', '0', '*'}};
byte rowPins[rows] = {4, 3, 2, 1}; // connect to the row pinouts of the keypad
byte colPins[cols] = {7, 6, 5};    // connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

const byte interruptPin = 21;
// volatile byte state = LOW;

LiquidCrystal lcd(50, 51, 45, 46, 47, 48);

bool door_is_open = false;
String door_status = "";

String entered_pass = "";
String password_status = "";
String timer_status = "";
String password = "1234";

int wrong_attempts = 0;

int sum_of_all_wrong_attempts = 1;

bool want_to_close_door = false;
bool want_to_change_password = false;
int time_to_wait = 10;
int time_to_close = 15;

void button_isr(void);
void update_status(void);
void update_lcd(void);
void reset_state(void);

// Servo motor
Servo servo;

// Buzzer
const int buzzer = 12;

//
#define LED_BLUE 20
#define LED_RED 19
void setup()
{
  pinMode(interruptPin, INPUT);
  pinMode(buzzer, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), button_isr, FALLING);
  servo.attach(9, 1000, 2000);
  lcd.begin(16, 4);

  servo.write(0);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, HIGH);

  Serial3.begin(9600);

  update_status();
  update_lcd();
}

bool old_pass_is_correct = false;
void loop()
{
  while (true)
  {

    if (wrong_attempts > MAX_ATTEMPTS)
    {
      time_to_wait--;

      if (time_to_wait == 0)
      {
        sum_of_all_wrong_attempts += 1;
        reset_state();
      }

      update_status();
      update_lcd();

      delay(500);
      continue;
    }

    if (want_to_close_door)
    {
      want_to_close_door = false;
      tone(buzzer, 4000); // Send 4000Hz sound signal...
      delay(500);         // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_BLUE, LOW);

      reset_state();

      update_status();
      update_lcd();
    }
    else if (want_to_change_password)
    {

      char key = keypad.getKey();

      if (key != NO_KEY)
      {

        if (old_pass_is_correct)
        {
          // enter new pass

          if (key == '#' || key == '*')
          {
            want_to_change_password = false;
            old_pass_is_correct = false;

            password = entered_pass;
            reset_state();
            update_status();
            update_lcd();
          }
          else
          {
            entered_pass += key;
          }
        }
        else // enter old pass
        {

          if (key == '#' || key == '*')
          {

            if (entered_pass == password)
            {
              old_pass_is_correct = true;
              // entered_pass = "";

              reset_state();
              door_status = "Enter new pass";
              update_lcd();
            }
            else
            {
              want_to_change_password = false;
              wrong_attempts += 1;
              entered_pass = "";
              password_status = "pass is False";

              update_status();
              update_lcd();
            }
          }
          else
          {
            entered_pass += key;
          }
        }
      }
      continue;
    }

    if (door_is_open)
    {
      time_to_close--;

      if (time_to_close == 0)
      {
        tone(buzzer, 4000); // Send 4000HZ sound signal...
        delay(500);         // ...for 1 sec
        noTone(buzzer);     // Stop sound...
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_BLUE, LOW);
        reset_state();
      }

      update_status();
      update_lcd();

      delay(500);
    }
    else
    // if (!door_is_open && wrong_attempts <= MAX_ATTEMPTS) // ELSE DO NOTHING
    {
      char key = keypad.getKey();
      if (key != NO_KEY)
      {
        if (key == '#' || key == '*')
        {
          if (entered_pass == password)
          {
            door_is_open = true;
            password_status = "pass is Correct";
            tone(buzzer, 1000); // Send 1KHz sound signal...
            delay(500);         // ...for 1 sec
            noTone(buzzer);     // Stop sound...
            digitalWrite(LED_RED, LOW);
            digitalWrite(LED_BLUE, HIGH);
            servo.write(45);
          }
          else
          {
            wrong_attempts++;
            if (wrong_attempts > MAX_ATTEMPTS)
            {
              tone(buzzer, 200); // Send 200Hz sound signal...
              delay(500);        // ...for 1 sec
              noTone(buzzer);    // Stop sound...
            }
            password_status = "pass is False";
          }

          entered_pass = "";

          update_status();
          update_lcd();
        }
        else
        {
          entered_pass += key;
        }
      }
    }
    // put your main code here, to run repeatedly:
  }
}

void update_lcd(void)
{
  lcd.clear();
  lcd.setCursor(0, 0);

  lcd.print(door_status);

  lcd.setCursor(0, 1);

  lcd.print(password_status);

  lcd.setCursor(0, 2);

  // lcd.print(time_to_close);
  lcd.print(timer_status);

  lcd.setCursor(0, 3);
}

void update_status(void)
{

  if (door_is_open)
  {
    wrong_attempts = 0;
    door_status = "door is open";
  }
  else
  {
    door_status = "door is closed";
    servo.write(0);
  }

  if (wrong_attempts > MAX_ATTEMPTS)
  {

    timer_status = "wait for: " + String(time_to_wait, DEC);
  }
  else if (door_is_open)
  {
    timer_status = "closed in: " + String(time_to_close, DEC);
  }
  else
  {
    timer_status = "";
  }
}

void button_isr(void)
{
  if (door_is_open)
  {

    want_to_close_door = true;
  }
  else
  {
    want_to_change_password = true;
    door_status = "Enter old pass";
    update_lcd();
  }
}

void reset_state(void)
{
  wrong_attempts = 0;
  door_is_open = false;
  time_to_wait = sum_of_all_wrong_attempts * 10;
  time_to_close = 15;
  password_status = "";
  entered_pass = "";
}
