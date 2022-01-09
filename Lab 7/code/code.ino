#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal.h>




// led pins
const int led[4] = {49, 50, 51, 52};


// keypad setup
const byte ROWS = 4; 
const byte COLS = 3;
char keys[ROWS][COLS] = {{'1', '2', '3'},
                         {'4', '5', '6'},
                         {'7', '8', '9'},
                         {'*', '0', '#'}};
byte rowPins[ROWS] = {31, 32, 33, 34}; 
byte colPins[COLS] = {28, 29, 30};
Keypad in = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


// lcd setup
const int rs = 22, en = 23, d4 = 24, d5 = 25, d6 = 26, d7 = 27;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);





String states[4] = {"PRE-WASH", "WASHING", "WATER-WASH", "DRYING"};

/*
 * hold the full state
 * 0: current state
 * 1: for time passed from duty
 * 2: duty time of pre wash
 * 3: duty time of washing
 * 4: duty time of water wash
 * 5: duty time of drying
 */
uint8_t full_state[6];
#define current_state full_state[0]
#define passed_time   full_state[1]
#define t_pre_wash    full_state[2]
#define t_washing     full_state[3]
#define t_water_wash  full_state[4]
#define t_drying      full_state[5]


void setup()
{
  memset(full_state, 0, 6);
  Wire.begin();

  for (int i = 0; i < 4; i++)
  {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }

  load();
}


void loop()
{
  set_led(0);

  // check times of states
  for (int state = 0; state < 4; state++)
    if (full_state[state+2] == 255)
      set_time(state);


  char key, start_state = 0;
  while (1)
  {
    if (current_state == 255)
    {
      do {
        lcd_print("start state: ", true, 1);
        //lcd_print("(1, 2, 3, or 4)", false, 2);

        key = in.waitForKey();
        if (is_num(key))
          start_state = key - '0';

        if (key == '#')
        {
          if (start_state > 4 || start_state < 1)
          {
            lcd_print("wrong !", true, 2);
            delay(1500);
            continue;
          }
          
          start_state--;
          break;
        }

        if (key == '*')
          reset_times();

      } while (true);

      current_state = start_state;
      save();
    }


    start_washing(current_state);
  }
}


void start_washing(int start_state)
{
  current_state = start_state;
  save();

  lcd_print("Starting ... ", true, 1);
  delay(1500);

  String s = "";

  set_led(0);
  for (int state = current_state; state < 4; state++)
  {
    current_state = state;
    save();

    set_led(state+1);

    if (passed_time == 255)
      passed_time = 0;
    save();

    
    char key;
    bool pause = false;
    while (passed_time < full_state[state+2])
    {
      key = in.getKey();
      if (key == '*')
        pause = !pause;

      if (pause)
      {
        lcd_print("Pause ...", false, 2);
        continue;
      }

      s = states[state];
      s.concat(" ");
      s.concat(String(full_state[state+2] - passed_time));
      s.concat("m");
      lcd_print(s, true, 1);
      // lcd_print(states[state], true, 1);

      // s = "time ";
      // s.concat(passed_time);
      // lcd_print(s, false, 2);

      delay(500);

      passed_time += 1;
      save();
    }

    passed_time = 255;
    save();
  }

  lcd_print("Finished ...", true, 0);
  set_led(5);

  current_state = 255;
  passed_time = 255;
  save();

  delay(1000);
}


void set_time(int state)
{
  String s = "";
  s.concat(states[state]);
  s.concat(" t?");
  lcd_print(s, true, 0);

  int time = 0;
  char key;
  while (true)
  {
    key = in.waitForKey();

    if (is_num(key))
      time = time*10 + (key - '0');

    if (key == '#')
      break;
  }

  time = (time >= 255) ? 254: time;

  if (time == 0)
    full_state[state+2] = 20;
  else
    full_state[state+2] = time;

  save();
}


void reset_times()
{
  for (int state = 0; state < 4; state++)
    set_time(state);
}


void save()
{
  Wire.beginTransmission(0b1010000);
  
  Wire.write(0);
  Wire.write(0);
  
  for (int i = 0; i < 6; i++)
    Wire.write(full_state[i]);
    
  Wire.endTransmission();
  delay(20);
}


void load()
{
  Wire.beginTransmission(0b1010000);
  
  Wire.write(0);
  Wire.write(0);
  
  Wire.endTransmission();
  
  Wire.requestFrom(0b1010000, (uint8_t)6);
  
  for (int i = 0; i < 6; i++)
    full_state[i] = Wire.read();
}


void lcd_print(String s, bool clean, int line)
{
  if (clean)
    lcd.clear();

  if (line == 1)
    lcd.setCursor(0, 0);
    
  if (line == 2)
    lcd.setCursor(0, 1);
    
  lcd.print(s);
}


bool is_num(char c)
{
  return (c >= '0' && c <= '9');
}


void set_led(int state)
{
  if (state == 0)
    for (int i = 0; i < 4; i++)
      digitalWrite(led[i], LOW);

  else if (state == 5)
    for (int i = 0; i < 4; i++)
      digitalWrite(led[i], HIGH);

  else
    for (int i = 0; i < 4; i++)
      if (i+1 == state)
        digitalWrite(led[i], HIGH);
      else
        digitalWrite(led[i], LOW);
}




      
