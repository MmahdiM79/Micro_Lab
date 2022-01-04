


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
  int num = Serial.parseInt();
  
  if (num)  
  {
    if (num >= 0 && num <= 9)
    {
      // trun off LEDs
      for (int i = 2; i <= 10; i++)
       digitalWrite(i, LOW);


      int currunt_LED = 10;
      for (int j = 0; j < num; j++, currunt_LED--)
        digitalWrite(currunt_LED, HIGH);
    }
  
    else
    {
      // trun off LEDs
      for (int i = 2; i <= 10; i++)
        digitalWrite(i, LOW);

      Serial.println("Invalid number");
    }
  }
}
