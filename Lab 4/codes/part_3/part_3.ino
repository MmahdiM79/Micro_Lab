#include <Servo.h>


Servo servo;

void setup() 
{
  Serial.begin(9600);
  servo.attach(9, 1000, 2000);
}


void loop() 
{
  if(Serial.available() > 0)
  {
    int degree = -1 * Serial.readString().toInt();
    Serial.println(degree);
    servo.writeMicroseconds(map(degree, -180, 180, 1000, 2000));
  }
}
