#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

#define PASSWORD "9831067"
String enteredPass = "";

String NAME = "ALI";

int curr_row = 0;
int curr_col = 0;

LiquidCrystal lcd(1, 0, 18, 19, 20, 21);

const byte rows = 4; //four rows
const byte cols = 4; //four columns
char keys[rows][cols] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', 'x'},
    {'1', '2', '3', '-'},
    {'#', '0', '=', '+'}};

byte rowPins[rows] = {30, 31, 32, 33}; //connect to the row pinouts of the keypad
byte colPins[cols] = {34, 35, 36, 37}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void first_part(void);
void second_part(void);
void third_part(void);
void fourth_part(void);
void go_one_step(int start_row, int start_col);
double calc(int op_1, int op_2, String oper);

void setup()
{
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  // lcd.print("hello world!");
}

void loop()
{

  // first_part();
  // second_part();
  // third_part();
  fourth_part();
}

double calc(int op_1, int op_2, char oper)
{
  switch (oper)
  {
  case '+':
    return (double)op_1 + op_2;
  case '-':
    return (double)op_1 - op_2;
  case 'x':
    return (double)op_1 * op_2;
  case '/':
    return op_1 / (double)op_2;
  default:
    return 0;
  }
}

String enteredText = "";
void third_part(void)
{
  char key = keypad.getKey();

  if (key != NO_KEY)
  {
    if (enteredText.equals(""))
    {
      lcd.clear();
      lcd.setCursor(0, 0);
    }

    lcd.print(key);
    if (key == '=')
    {
      int index = enteredText.indexOf("+");

      if (index == -1)
      {
        index = enteredText.indexOf("-");

        if (index == -1)
        {
          index = enteredText.indexOf("/");
          if (index == -1)
          {
            index = enteredText.indexOf("x");
          }
        }
      }

      int operand_1 = enteredText.substring(0, index).toInt();
      int operand_2 = enteredText.substring(index + 1, enteredText.length()).toInt();
      char oper = enteredText.charAt(index);

      double result = calc(operand_1, operand_2, oper);
      lcd.setCursor(0, 1);
      lcd.print(result);
      enteredText = "";
    }
    else
    {
      enteredText = enteredText + key;
    }
  }
}

char c = '*';
void fourth_part(void)
{
  lcd.print(c);

  delay(300);
  lcd.clear();
  curr_col = (curr_col + 1) % 16;
  curr_row = (curr_row + 1) % 2;
  lcd.setCursor(curr_col, curr_row);

}

void second_part(void)
{

  char key = keypad.getKey();

  if (key != NO_KEY)
  {
    if (enteredPass.equals(""))
    {
      lcd.clear();
    }

    lcd.print(key);

    if (key == '#')
    {
      lcd.clear();

      if (enteredPass.equals(PASSWORD))
      {
        lcd.print("correct pass");
      }
      else
      {
        lcd.print("wrong pass");
      }

      enteredPass = "";
    }
    else
    {
      enteredPass = enteredPass + key;
    }
  }
}

void first_part(void)
{

  while (true)
  {

    go_one_step(curr_row, curr_col);
    delay(300);

    lcd.clear();

    curr_col = (curr_col + 1) % 16;
    if (curr_col == 0)
    {
      curr_row = (curr_row + 1) % 2;
    }
  }
}

void go_one_step(int start_row, int start_col)
{
  lcd.setCursor(start_col, start_row);
  for (char &c : NAME)
  {
    lcd.print(c);

    start_col = (start_col + 1) % 16;
    if (start_col == 0)
    {
      start_row = (start_row + 1) % 2;
      if (start_row == 0)
      {
        //go to first line(row)
        lcd.setCursor(0, 0);
      }
      else
      {
        //go to new line
        lcd.setCursor(0, 1);
      }
    }
  }
}