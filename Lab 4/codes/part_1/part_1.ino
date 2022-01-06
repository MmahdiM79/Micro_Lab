#include <Servo.h>


Servo motor;
int degree; 


void setup() 
{
  motor.attach(9, 1000, 2000);
  Serial.begin(9600);
}

void loop() 
{
  while(1)
  {
    for (degree = 0; degree <= 90; degree++) 
    { 
      Serial.println(motor.read());
      motor.write(degree);              
      delay(50);                       
    }
    delay(1000);
    for (degree = 90; degree >= 0; degree--) 
    { 
      Serial.println(motor.read());
      motor.write(degree);              
      delay(50);                       
    }
  }

//    motor.write(90);              
//    delay(2000);
//    motor.write(0);              
//    delay(2000);
}
