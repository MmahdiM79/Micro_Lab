#include "pitches.h"
#include "jingle_bells.h"
#include "ode_to_joy.h"
#include "my_own_summer.h"
#include <Keypad.h>


const byte ROWS = 4; // four rows
const byte COLS = 3; // three columns
char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};
byte rowPins[ROWS] = {22, 23, 24, 25}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {26, 27, 28};     // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const float arduino_clockrate = 1.0f;

const int piezo_pin = 2;
const int start_pin = 3;

float scale = 1.0;

void setup()
{
  pinMode(start_pin, INPUT);
  pinMode(A1, INPUT);
  
  while(digitalRead(start_pin) == LOW);
  
  player(jingle_bells_intro, introNoteDurations2, sizeof(jingle_bells_intro) / sizeof(int), durationMultiplier2);
  player(my_own_summer_intro, introNoteDurations3, sizeof(my_own_summer_intro) / sizeof(int), durationMultiplier3);
  player(ode_to_joy_intro, introNoteDurations4, sizeof(ode_to_joy_intro) / sizeof(int), durationMultiplier4);
  
  int section = 0;
}

void loop() 
{
    char key = keypad.waitForKey();

    if(key == '1'){
      player(jingle_bells, noteDurations2, sizeof(jingle_bells) / sizeof(int), durationMultiplier2);
      delay(200);
    }
    else if(key == '2'){
      player(my_own_summer, noteDurations3, sizeof(my_own_summer) / sizeof(int), durationMultiplier3);
      delay(200);
    }
    else if(key == '3'){
      player(ode_to_joy, noteDurations4, sizeof(ode_to_joy) / sizeof(int), durationMultiplier4);
      delay(200);
    }
}

void player(int *notes, double *durations, int lengthOfArray, float durationMultiplier) 
{
  for(int thisNote = 0; thisNote < lengthOfArray; thisNote++) 
  {
    int noteDuration = (int)(1000 / durations[thisNote]);
    scale = analogRead(A1) / 512.0;
    
    if (notes[thisNote] != SILENCE)
      tone(piezo_pin, (int)(notes[thisNote] * (16.0f / arduino_clockrate) * scale), noteDuration * durationMultiplier * (arduino_clockrate / 16.0f));
      
    delay((int)(noteDuration * durationMultiplier * (arduino_clockrate / 16.0f)));
  }
}
