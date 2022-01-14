#define ROW_1 30  
#define ROW_2 31  
#define ROW_3 32   
#define ROW_4 33  
#define ROW_5 34  
#define ROW_6 35  
#define ROW_7 36   
#define ROW_8 37   

#define COL_1 22  
#define COL_2 23   
#define COL_3 24   
#define COL_4 25  
#define COL_5 26   
#define COL_6 27   
#define COL_7 28  
#define COL_8 29

#define red_led_pin 41
#define yellow_led_pin 42


const byte rows[] = {ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8};

byte board_bits[] = {0,0,0,0,0,0,0,0};
byte board[] = {0,0,0,
                0,0,0,
                0,0,0};

void setColumns(byte b) 
{
    digitalWrite(COL_1, (~b >> 0) & 0x01); // Get the 1st bit: 10000000
    digitalWrite(COL_2, (~b >> 1) & 0x01); // Get the 2nd bit: 01000000
    digitalWrite(COL_3, (~b >> 2) & 0x01); // Get the 3rd bit: 00100000
    digitalWrite(COL_4, (~b >> 3) & 0x01); // Get the 4th bit: 00010000
    digitalWrite(COL_5, (~b >> 4) & 0x01); // Get the 5th bit: 00001000
    digitalWrite(COL_6, (~b >> 5) & 0x01); // Get the 6th bit: 00000100
    digitalWrite(COL_7, (~b >> 6) & 0x01); // Get the 7th bit: 00000010
    digitalWrite(COL_8, (~b >> 7) & 0x01); // Get the 8th bit: 00000001
}

void  show()
{
    for (byte i = 0; i < 8; i++) 
    {
      setColumns(board_bits[i]);
          
      digitalWrite(rows[i], HIGH);
      delay(1); 
      digitalWrite(rows[i], LOW);  
    }
}

int set(char block, byte player)
{
  if (block < '1' || block > '9')
    return 0;
    
  int i = block - '0' - 1;
  if (board[i] != 0)
    return 0;

  board[i] = player;
  
  switch (block)
  {
    case '1':
      if (player == 1)
      {
        board_bits[0] = board_bits[0] | B11000000;
        board_bits[1] = board_bits[1] | B10000000;
      }
      else
      {
        board_bits[0] = board_bits[0] | B01000000;
        board_bits[1] = board_bits[1] | B11000000;
      }
    break;


    case '2':
      if (player == 1)
      {
        board_bits[0] = board_bits[0] | B00011000;
        board_bits[1] = board_bits[1] | B00010000;
      }
      else
      {
        board_bits[0] = board_bits[0] | B00001000;
        board_bits[1] = board_bits[1] | B00011000;
      }
    break;


    case '3':
      if (player == 1)
      {
        board_bits[0] = board_bits[0] | B00000011;
        board_bits[1] = board_bits[1] | B00000010;
      }
      else
      {
        board_bits[0] = board_bits[0] | B00000001;
        board_bits[1] = board_bits[1] | B00000011;
      }
    break;


    case '4':
      if (player == 1)
      {
        board_bits[3] = board_bits[3] | B11000000;
        board_bits[4] = board_bits[4] | B10000000;
      }
      else
      {
        board_bits[3] = board_bits[3] | B01000000;
        board_bits[4] = board_bits[4] | B11000000;
      }
    break;


    case '5':
      if (player == 1)
      {
        board_bits[3] = board_bits[3] | B00011000;
        board_bits[4] = board_bits[4] | B00010000;
      }
      else
      {
        board_bits[3] = board_bits[3] | B00001000;
        board_bits[4] = board_bits[4] | B00011000;
      }
    break;


    case '6':
      if (player == 1)
      {
        board_bits[3] = board_bits[3] | B00000011;
        board_bits[4] = board_bits[4] | B00000010;
      }
      else
      {
        board_bits[3] = board_bits[3] | B00000001;
        board_bits[4] = board_bits[4] | B00000011;
      }
    break;


    case '7':
      if (player == 1)
      {
        board_bits[6] = board_bits[6] | B11000000;
        board_bits[7] = board_bits[7] | B10000000;
      }
      else
      {
        board_bits[6] = board_bits[6] | B01000000;
        board_bits[7] = board_bits[7] | B11000000;
      }
    break;


    case '8':
      if (player == 1)
      {
        board_bits[6] = board_bits[6] | B00011000;
        board_bits[7] = board_bits[7] | B00010000;
      }
      else
      {
        board_bits[6] = board_bits[6] | B00001000;
        board_bits[7] = board_bits[7] | B00011000;
      }
    break;


    case '9':
      if (player == 1)
      {
        board_bits[6] = board_bits[6] | B00000011;
        board_bits[7] = board_bits[7] | B00000010;
      }
      else
      {
        board_bits[6] = board_bits[6] | B00000001;
        board_bits[7] = board_bits[7] | B00000011;
      }
    break;
  }

  return 1;
}


void set_led(byte turn)
{
  if (turn == 1)
  {
    digitalWrite(red_led_pin, LOW);
    digitalWrite(yellow_led_pin, HIGH);
  }
  else
  {
    digitalWrite(red_led_pin, HIGH);
    digitalWrite(yellow_led_pin, LOW);
  }
}


int end_game()
{
  for (int i = 0; i < 9; i += 3)
    if (board[i] == board[i+1] && board[i] == board[i+2])
      return board[i];

  for (int i = 0; i < 3; i++)
    if (board[i] == board[i+3] && board[i] == board[i+6])
      return board[i];

  if (board[0] == board[4] && board[0] == board[8])
    return board[0];

  if (board[2] == board[4] && board[2] == board[6])
    return board[2];

  for (int i = 0; i < 9; i++)
    if (board[i] == 0)
      return 0;
      
  return 2;
}


void set_res(int res)
{
  if (res == 1)
  {
    board_bits[0] = B00000000;
    board_bits[1] = B01100110;
    board_bits[2] = B01100110;
    board_bits[3] = B00000000;
    board_bits[4] = B00000000;
    board_bits[5] = B01100110;
    board_bits[6] = B00111100;
    board_bits[7] = B00011000;
  }
  else if (res != 2)
  {
    board_bits[0] = B00000000;
    board_bits[1] = B01100110;
    board_bits[2] = B01100110;
    board_bits[3] = B00000000;
    board_bits[4] = B00000000;
    board_bits[5] = B00011000;
    board_bits[6] = B00111100;
    board_bits[7] = B01100110;
  }
  else
  {
    board_bits[0] = B00000000;
    board_bits[1] = B01100110;
    board_bits[2] = B01100110;
    board_bits[3] = B00000000;
    board_bits[4] = B01111110;
    board_bits[5] = B01111110;
    board_bits[6] = B00000000;
    board_bits[7] = B00000000;
  }
}


void reset()
{
  for (int i = 0; i < 8; i++)
  {
    board_bits[i] = 0;
    board[i] = 0;
  }

  board[8] = 0;
}


void setup_matrix()
{
  for (byte i = 22; i <= 37; i++)
    pinMode(i, OUTPUT);

  pinMode(red_led_pin, OUTPUT);
  pinMode(yellow_led_pin, OUTPUT);
}
