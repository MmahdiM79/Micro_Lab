#include <Servo.h>

Servo myservo;

void setup() 
{
  Serial3.begin(9600);
  myservo.attach(9);
}


void loop() 
{
  int degree = analogRead(A0);
  degree = map(degree, 0, 1023, 0, 180);
  myservo.write(degree);
  delay(10);
}
