#include <Servo.h>
#include <Keypad.h>


const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {{'7','8','9','/'},
                         {'4','5','6','*'},
                         {'1','2','3','-'},
                         {'C','0','=','+'}};

byte rowPins[ROWS] = {22, 23, 24, 25}; 
byte colPins[COLS] = {26, 27, 28, 29}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );




Servo servo;
int potpin = A0;  
   
void setup() 
{
  servo.attach(9,1000,2000);  
  Serial.begin(9600);
}


int degree = 0;
void loop() 
{
  char key = keypad.getKey(); 
   
  if(key == '=')
  {
    degree -= 180;
    Serial.println(degree);
    degree = map(degree , -180, +180 ,0 , 180);
    servo.write(degree);
    delay(1000);
    servo.write(0);
    delay(1000);
    degree = 0;  
    Serial.println("end ...");
  }
  else if(key >= '0' && key <= '9')
  {
    degree *= 10;
    degree += key - '0';
    Serial.println("degree: " + degree);          
  }
}
