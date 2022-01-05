#include <Keypad.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(13, 12, 8, 9, 10, 11);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {{'7', '8', '9', '/'},
                         {'4', '5', '6', '*'},
                         {'1', '2', '3', '-'},
                         {'C', '0', '=', '+'}};

const byte rowPins[ROWS] = {29, 30, 31, 32};
const byte colPins[COLS] = {33, 34, 35, 36};

Keypad kp = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);




bool check_password(char pass[7], byte len)
{
  if (len != 7)
    return false;

   char password[] = {'9', '8', '3', '1', '1', '3', '9'};
   for (int i = 0; i < 7; i++)
    if (password[i] != pass[i])
      return false;

   return true;
}


void setup() 
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
}


void loop() 
{
  int i = 0;
  char key = '0';

  int k = 0;
  char pass[7] = {'0'};

  
  while (1)
  {
    key = kp.getKey();

    if (key)
    {
      if (key <= '9' && key >= '0')
      {
        lcd.setCursor(i++, 0);
        lcd.print(key);

        pass[k++] = key;
      }

      if (key == '=')
      {
        if (check_password(pass, k))
        {
          lcd.setCursor(0, 1);
          lcd.print("correct pasword");
          delay(500);
          return 0;
        }
        else
        {
          lcd.setCursor(0, 1);
          lcd.print("wrong pasword");
          delay(500);
          lcd.clear();

          i = 0;
          k = 0;
        }
      }
    }
  }
}
