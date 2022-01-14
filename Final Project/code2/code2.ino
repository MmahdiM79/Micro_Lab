#include <Keypad.h>
#include "led_matrix.h"


const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {{'1', '2', '3'},
                         {'4', '5', '6'},
                         {'7', '8', '9'},
                         {'*', '0', '#'}};

byte rowPins[ROWS] = {50, 51, 52, 53};
byte colPins[COLS] = {49, 48, 47};

Keypad pad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);



#define THIS 1
#define THAT -1

byte turn;
byte moves;

void setup() 
{
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  Serial.begin(9600);
  setup_matrix();

  for (int i = 47; i <= 53; i++)
    pinMode(i, INPUT);

  turn = THAT;
  moves = 0;
}


void loop()
{
  char key;
  while (!end_game())
  {
    set_led(turn);
    show();

    if (turn == THIS)
    {
      do {
        show();
        
        key = pad.getKey();
        if (moves == 0 && key == '0')
          break;
          
      }while(set(key, THIS) != 1);
      
      Serial.write(key);
      if (key != '0')
        moves++;
      
      turn = THAT;
    }
    else
    {
      while (!Serial.available())
        show();

      key = Serial.read();
      if (key != '0')
      {
        moves++;
        set(key, THAT);
      }

      turn = THIS;
    }
  }

  set_res(end_game());
  for (int i = 0; i < 70; i++)
    show();

  reset();
  turn = THAT;
  moves = 0;
}
