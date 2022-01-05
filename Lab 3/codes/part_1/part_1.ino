#include <Keypad.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(13, 12, 8, 9, 10, 11);

void setup() 
{
  

  lcd.begin(15, 2);
  lcd.setCursor(0, 0);
}


void loop() 
{
  int i = 0, j = 0;
  
  while (i < 60)
  {
    lcd.clear();
    lcd.setCursor(i%15, j);

 
    lcd.print("Mahdi");
    delay(150);

    i++;
    j = ((i/15)%2 == 1) ? 1: 0;
  }
}
