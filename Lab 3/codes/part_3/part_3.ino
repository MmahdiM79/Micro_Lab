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






void setup() 
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
}


void loop() 
{
  int i = 0;
  char key = '0';

  
  int a = 0, b = 0;
  byte current_num = 1;
  
  char operand = '\0';

  bool finished = false;
  
  while (1)
  {
    key = kp.getKey();

    if (key)
    {
      if ((key <= '9' && key >= '0') && !finished)
      {
        lcd.setCursor(i++, 0);
        lcd.print(key);

        if(current_num == 1)
        {
          a *= 10;
          a += key - '0';
        }
        else
        {
          b *= 10;
          b += key - '0';
        }
      }

      else if (key == '=' && !finished)
      {
        int res;
        switch (operand)
        {
          case '/': res = a/b; break;
          case '*': res = a*b; break;
          case '-': res = a-b; break;
          case '+': res = a+b; break;
        }

        finished = true;
       
        lcd.setCursor(0, 1);
        lcd.print("=");
        lcd.setCursor(1, 1);
        lcd.print(res);
      }

      else if (key == 'C' && finished)
      {
        a = b = 0;
        current_num = 1;
        finished = false;
        i = 0;

        lcd.clear();
      }

      else if (!finished)
      {
        lcd.setCursor(i++, 0);
        lcd.print(key);

        operand = key;
        current_num = 2;
      }
    }
  }
}
