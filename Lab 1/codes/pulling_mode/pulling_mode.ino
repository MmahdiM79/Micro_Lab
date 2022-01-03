#define b1 12
#define b2 11
#define b3 10

int len_name = 5;// or = strlen("mahdi");

bool in_range(int pin_num)
{
  return (pin_num < 6 && pin_num >= 0);
}




void setup() 
{
  // set buttons
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);

  // set LEDs
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}



void loop() 
{
  // button 1
  if(digitalRead(b1) == LOW)
  {
    for (int i = 24; i >= -1 ; i--)
    {
      int j = i%6;

      if (in_range(j-1))
        digitalWrite(j-1, HIGH);
      if (in_range(j))
        digitalWrite(j, HIGH);
      if (in_range(j+1))
        digitalWrite(j+1, HIGH);

      delay(50);

      if (in_range(j-1))
        digitalWrite(j-1, LOW);
      if (in_range(j))
        digitalWrite(j, LOW);
      if (in_range(j+1))
        digitalWrite(j+1, LOW);
    }
  }




  if(digitalRead(b2) == LOW)
  {
    for (int i = 0; i < len_name; i++)
    {
      for (int j = 0; j < 6; j++)
        digitalWrite(j, LOW);

      delay(300);

      for (int j = 0; j < 6; j++)
        digitalWrite(j, HIGH);

      delay(300);
    }
  }




  if (digitalRead(b3) == LOW)
  {
    for (int j = 0; j < 6; j++)
        digitalWrite(j, LOW);
  }
}
