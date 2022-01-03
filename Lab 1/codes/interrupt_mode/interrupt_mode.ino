#define b1 18
#define b2 19
#define b3 20

int len_name = 5;// or = strlen("mahdi");

bool in_range(int pin_num)
{
  return (pin_num < 6 && pin_num >= 0);
}



void b1_intrpt()
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

      delay(12000);

      if (in_range(j-1))
        digitalWrite(j-1, LOW);
      if (in_range(j))
        digitalWrite(j, LOW);
      if (in_range(j+1))
        digitalWrite(j+1, LOW);
    }
}



void b2_intrpt()
{
  for (int i = 0; i < len_name; i++)
    {
      for (int j = 0; j < 6; j++)
        digitalWrite(j, LOW);

      delay(50000);

      for (int j = 0; j < 6; j++)
        digitalWrite(j, HIGH);

      delay(50000);
    }
}



void b3_intrpt()
{
  for (int j = 0; j < 6; j++)
        digitalWrite(j, LOW);
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


  attachInterrupt(digitalPinToInterrupt(b1), b1_intrpt, FALLING);
  attachInterrupt(digitalPinToInterrupt(b2), b2_intrpt, FALLING);
  attachInterrupt(digitalPinToInterrupt(b3), b3_intrpt, FALLING);
}



void loop() {}
