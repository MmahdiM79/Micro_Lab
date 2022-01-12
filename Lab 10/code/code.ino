#include "CM5x5.h"

int led_pins[15] = {53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39};
int n_leds = 15;
int clk_pin = 22;


void setup()
{
  Serial.begin(9600);

  for (int i = 0; i < n_leds; i++)
    pinMode(led_pins[i], OUTPUT);

  pinMode(clk_pin, INPUT);
}

void loop()
{
  String s;
  
  while (1)
  {
    Serial.println("please enter a string:  ");
    while (Serial.available() == 0);

    s = Serial.readString();
    s.toLowerCase();
    Serial.print("your given string:  ");
    Serial.println(s);
    

    int matrix[5][(s.length()-1)*5];
    for (int i = 0; i < 5; i++)
      for (int j = 0; j < (s.length()-1)*5; j++)
        matrix[i][j] = 0;
        
    int hold[5][5] = {0};
    for (int i = 0; i < 3 && i < s.length()-1; i++)
    {
      setMatrix(s[i], hold);
      for (int j = 0; j < 5; j++)
        for (int k = 0; k < 5; k++)
          matrix[j][k+(i*5)] = hold[j][k];
    }

    Serial.println();
    Serial.println();
    Serial.println("wait for process ... (do not type anything)");
    Serial.println();
    Serial.println();

 
    for (int i = 4, t = 0; i >= 0; i--)
    {
      while (digitalRead(clk_pin) == 1);
      for (int j = 0; j < n_leds && j < (s.length()-1)*5; j++)
        digitalWrite(led_pins[j], matrix[i][j]);

      delay(170);
    }
    for (int j = 0; j < n_leds; j++)
        digitalWrite(led_pins[j], 0);
        
    delay(2000);
  }
}
