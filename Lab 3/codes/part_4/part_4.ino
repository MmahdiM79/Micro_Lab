#include <Keypad.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(13, 12, 8, 9, 10, 11);



void setup() 
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
}


void loop() 
{
  int i = 0, j = 0;
  
  while(1)
  {
    lcd.clear();

    lcd.setCursor(i, j);
    lcd.print("@");
    delay(100);

    j = (j+1)%2;
    i++;
    i %= 16;
  }
}
