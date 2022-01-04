#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {{'1','2','3'},
                             {'4','5','6'},
                             {'7','8','9'},
                             {'*','0','#'}};
                             
byte rowPins[ROWS] = {49, 50, 51, 52}; 
byte colPins[COLS] = {48, 47, 46}; 

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 





void setup()
{
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);


  // trun off LEDs
  for (int i = 2; i <= 10; i++)
    digitalWrite(i, LOW);
}



void loop()
{ 
  Serial.write(customKeypad.getKey());
}
