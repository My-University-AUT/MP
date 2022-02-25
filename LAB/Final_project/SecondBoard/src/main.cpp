#include <Arduino.h>
#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

const int rows = 4;
const int cols = 3;

char keys[rows][cols] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};
byte rowPins[rows] = {43, 44, 45, 46}; // connect to the row pinouts of the keypad
byte colPins[cols] = {47, 48, 49};     // connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

LiquidCrystal lcd(33, 34, 35, 36, 37, 38, 39, 40, 41, 42);

int grid[3][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}};

void update_lcd();
bool update_grid(int i, int user);
void reset_game(void);
bool check_game_is_over();

bool myTurn = false;
bool gameIsOver = false;
const int user_number = 2;

void setup()
{
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);

  lcd.begin(16, 4);
  update_lcd();
}

void loop()
{
  // read from port 1, send to port 0:
  if (Serial1.available() > 0)
  {
    // TODO
    char enteredChar = Serial1.read();
    if (enteredChar == '#')
    {
      reset_game();
      // TODO reset the game
    }
    else if (enteredChar >= '1' && enteredChar <= '9')
    {
      myTurn = !myTurn;
      int choice = enteredChar - 48;
      update_grid(choice, 3 - user_number);

      gameIsOver = check_game_is_over();
      update_lcd();
    }
  }

  char enteredChar = keypad.getKey();
  if (enteredChar != NO_KEY)
  {
    // for debugging
    Serial.print(enteredChar);

    if (enteredChar == '#')
    {
      // TODO
      reset_game();
      Serial1.print(enteredChar);
    }

    if (enteredChar >= '1' && enteredChar <= '9' && myTurn && !gameIsOver)
    {
      // TODO Change user_number for second user
      int choice = enteredChar - 48;
      int res = update_grid(choice, user_number);
      if (res == true)
      {
        gameIsOver = check_game_is_over();
        myTurn = false;
        update_lcd();
        Serial1.print(enteredChar);
      }
    }
  }
}

bool update_grid(int i, int user)
{
  if (i >= 1 && i <= 9)
  {
    int row = (i - 1) / 3;
    int col = (i - 1) % 3;

    if (grid[row][col] == 0)
    {
      // if grid is empty
      grid[row][col] = user;
      return true;
    }
  }

  return false;
}

char get_char(int i)
{
  switch (i)
  {
  case 1:
    return 'X';
  case 2:
    return 'O';
  default:
    return '#';
  }
}
void update_lcd()
{
  lcd.clear();

  for (int i = 0; i < 3; i++)
  {
    lcd.setCursor(6, i);
    for (int j = 0; j < 3; j++)
    {
      char c = get_char(grid[i][j]);
      lcd.print(c);
      lcd.print(" ");
    }
  }
  if (gameIsOver)
  {
    lcd.setCursor(0, 3);
    lcd.print("game is over!");
  }
  else
  {
    lcd.setCursor(0, 3);
    if (myTurn)
    {
      lcd.print("my turn");
    }
    else
    {
      lcd.print("opponent turn");
    }
  }
}

bool check_game_is_over()
{
  for (int i = 0; i < 3; i++)
  {
    // check rows
    if (grid[i][0] != 0 && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
    {
      return true;
    }
  }
  for (int i = 0; i < 3; i++)
  {
    // check cols
    if (grid[0][i] != 0 && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
    {
      return true;
    }
  }

  if (grid[0][0] != 0 && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
  {
    return true;
  }

  if (grid[0][2] != 0 && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
  {
    return true;
  }

  return false;
}

void reset_game(void)
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      grid[i][j] = 0;
    }
  }
  if (user_number == 1)
  {
    myTurn = true;
  }
  else
  {
    myTurn = false;
  }
  gameIsOver = false;
  update_lcd();
}