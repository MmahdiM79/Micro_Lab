#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>


/* setup keyboard */
const byte ROWS = 4; 
const byte COLS = 3;
char keys[ROWS][COLS] = {{'1','2','3'},
                         {'4','5','6'},
                         {'7','8','9'},
                         {'*','0','#'}};
byte rowPins[ROWS] = {31, 32, 33, 34};
byte colPins[COLS] = {30, 29, 28};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

/* setup display */
LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

/* setup servo */
Servo servo;

/* pins */
const int open_LED = 1;
const int close_LED = 0;
const int door_pin = 2;
const int buz_pin = 3;
const int servo_pin = 9;

/* global variables */
String pass = "0000";
String entered_pass = "";
int wrong_pass_counter = 0;


void setup()
{
  lcd.begin(16, 1);
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Close.");
  
  servo.attach(servo_pin);
  servo.write(0);
  
  pinMode(open_LED, OUTPUT);
  pinMode(close_LED, OUTPUT);
  pinMode(buz_pin, OUTPUT);
  pinMode(door_pin, INPUT);
  
  digitalWrite(open_LED, LOW);
  digitalWrite(close_LED, HIGH);
  digitalWrite(door_pin, LOW);
}
  
void loop()
{
  lcd_print("Close.");
  
  char key;
  do { key = keypad.getKey(); }
  while(!key);
  buz(0.2);

  if (key >= '0' && key <= '9')
    entered_pass.concat(key);
  
  else if (key == '*')
    check_pass();

  else // key == '#'
    change_pass();
}



/* functions */
int char_to_int(char c) { return c - '0'; }

bool is_entered_pass_correct() { return entered_pass == pass; }


void open_door()
{
  lcd_print("door opened");
  servo.write(90);
  digitalWrite(open_LED, HIGH);
  digitalWrite(close_LED, LOW);
  buz(0.5);
}


void close_door()
{
  lcd_print("door closed");
  servo.write(0);
  digitalWrite(open_LED, LOW);
  digitalWrite(close_LED, HIGH);
  buz(0.5);
}


void buz(float second) 
{ 
  tone(buz_pin, 500);
  delay(int(second*250)); 
  noTone(buz_pin);
}


void change_pass()
{
  lcd_print("old pass then *");
  
  char key;

  entered_pass = "";
  do {
    do { key = keypad.getKey(); }
    while(!key);
    buz(0.2);

    if (key >= '0' && key <= '9')
      entered_pass.concat(key);
      
  } while(key != '*');

  if(!is_entered_pass_correct())
  {
    buz_print("wrong pass", 2);
    entered_pass = "";
    return;
  }
  entered_pass = "";


  String new_pass = "", hold = "";

  lcd_print("new pass then *");
  do {
    do { key = keypad.getKey(); }
    while(!key);
    buz(0.2);

    if (key >= '0' && key <= '9')
      new_pass.concat(key);
      
  } while(key != '*');

  lcd_print("re enter then *");
  do {
    do { key = keypad.getKey(); }
    while(!key);
    buz(0.2);

    if (key >= '0' && key <= '9')
      hold.concat(key);
    
  } while(key != '*');

  if (hold != new_pass)
  {
    buz_print("dosen't match!", 1.5);
    return;
  }

  pass = new_pass;
  buz_print("pass changed", 1.5);
}


void check_pass()
{
  if (!is_entered_pass_correct())
  {
    buz_print("wrong pass", 2);
    entered_pass = "";
    wrong_pass_counter++;
    if (wrong_pass_counter%4 == 0)
    {
      lcd_print("disable " + String(wrong_pass_counter/4) + "min");
      delay((wrong_pass_counter/4)*10000);
    }
    return;
  }
  wrong_pass_counter = 0;

  open_door();

  int open_time = millis();
  int buz_time = open_time;
  
  do {
    lcd_print("time: " + String((millis()-open_time)/300) + "s");
    delay(250);
    
    if (millis() - buz_time > 10*350)
      buz(0.3);
      
    if (keypad.getKey() == '#')
      buz_time = millis();

    digitalWrite(door_pin, LOW);
    
  } while(digitalRead(door_pin) != HIGH);
  
  for (int i = 0; i < 10; i++)
    digitalWrite(door_pin, LOW);

  close_door();
  entered_pass = "";
}


void lcd_print(String s)
{
  lcd.clear();
  lcd.print(s);
}


void buz_print(String s, float second)
{
  lcd_print(s);
  buz(second);
  lcd_print("");
}
