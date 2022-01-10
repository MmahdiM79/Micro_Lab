#include <SPI.h>

#define SS 53
#define MOSI 51
#define MISO 50
#define SCK 52

volatile int i = 0;
byte buff[13];

void setup()
{
  Serial.begin(9600);
  Serial.println("This is slave");
  pinMode(SS, INPUT_PULLUP);
  pinMode(MOSI, OUTPUT);
  pinMode(SCK, INPUT);
  SPCR |= _BV(SPE);
  SPCR |= _BV(SPIE);     // interrupts
  SPI.attachInterrupt(); // allows SPI interrupt
  Serial.println("This is slave");
}

void loop()
{
  if (i == 13)
  {
    Serial.print("Received: ");
    String myString = String((char *)buff);
    Serial.println(myString);
    i = 0;
  }
}

ISR(SPI_STC_vect)
{
  Serial.print(i);
  Serial.print("=");
  Serial.print((char)SPDR);
  Serial.println("");
  buff[i] = SPDR;
  i++;
}
