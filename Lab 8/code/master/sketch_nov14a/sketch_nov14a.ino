#include <SPI.h>

#define SS 48
#define SS1 49

byte NAME_STU[13] = {'s', 'a', 'l', 'e','h', '9', '8', '3', '1', '1', '1', '2'};
byte HI_saleh[13] = {'H', 'i', 's', 'a', 'l', 'e','h', '3', '1', '1', '1', '2'};

const int MOD = 1;

void setup()
{
  pinMode(SS, OUTPUT);
  pinMode(SS1, OUTPUT);
  digitalWrite(SS, HIGH);
  digitalWrite(SS1, HIGH);

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  if (MOD==1)
      digitalWrite(SS, LOW); //enable slave 0
  Serial.begin(9600);
  Serial.println("This is master");
}
void loop()
{
  switch (MOD)
  {
  case 1:
    sendName();
    break;
  case 2:
    sendHiMyName();
    break;
  case 3:
    sendTL();
    break;
  default:
    break;
  }
}

void sendName()
{
  for (int i = 0; i < 13; i++)
  {
    SPI.transfer(NAME_STU[i]);
    Serial.print((char)NAME_STU[i]);
    delay(30);
  }
  Serial.println("");
  delay(1000);
}

void sendHiMyName()
{
  Serial.println("send name and stunumber");
  digitalWrite(SS, LOW); //Enable Slave0
  delay(100);
  for (int i = 0; i < 13; i++)
  {
    SPI.transfer(NAME_STU[i]);
    Serial.print((char)NAME_STU[i]);
    delay(30);
  }
  delay(50);
  digitalWrite(SS, HIGH); //disable Slave0
  delay(500);
  Serial.println("");
  Serial.println("send hi my name");
  delay(50);
  digitalWrite(SS1, LOW); //Enable Slave1
  delay(100);
  for (int i = 0; i < 13; i++)
  {
    SPI.transfer(HI_saleh[i]);
    Serial.print((char)HI_saleh[i]);
    delay(30);
  }
  Serial.println("");
  delay(50);
  digitalWrite(SS1, HIGH); //disable Slave1
  delay(1000);
}

void sendTL()
{
  digitalWrite(SS, LOW); //Enable Slave0
  delay(50);
  float temp = analogRead(A0);
  temp *= 0.48828125;
  Serial.println("temperature= " + String(temp) + " C^");
  byte tempTemperature[2];
  tempTemperature[0] = (int)temp;
  tempTemperature[1] = (int)temp >> 8;
  //sendNewData();
  delay(50);
  for (int i = 0; i < 2; i++)
  {
    SPI.transfer(tempTemperature[i]);
    delay(30);
  }
  delay(50);
  digitalWrite(SS, HIGH); //disable Slave0
  delay(500);
  digitalWrite(SS1, LOW); //Enable Slave1
  delay(50);

  int analogLight = analogRead(A1);
  //  analogLight = map(analogLight, 0, 1023, 0, 990);
  byte tempLight[2];
  tempLight[0] = analogLight;
  tempLight[1] = analogLight >> 8;
  Serial.println("Light= " + String(analogLight));
  //sendNewData();
  delay(50);
  for (int i = 0; i < 2; i++)
  {
    SPI.transfer(tempLight[i]);
    delay(30);
  }
  delay(50);
  digitalWrite(SS1, HIGH); //disable Slave1
  delay(500);
}
