#include <ipst.h>

int value = 0;
int count, block;
int started;

void setup()
{
  Serial.begin(9600);
  
  out(18, 1);
  count = 0;
  block = 0;
  started = 0;
  glcdMode(3);
} 
  
void loop()
{
  if(in(16) == 0)
  {
    started = 1;
  }
  
  if(started == 1)
  {
    motor(1, 10);
    motor(2, -10);
    value = analog(0);
    
//  Serial.println(value);
    if(value < 500 && block == 1)
    {
      count ++;
      delay(10);
      block = 0;
      Serial.println(count);
    
    }
    if(value > 700 && block == 0)
    {
      block = 1;
      count ++;
      delay(10);
    }
    if(count == 5)
    {
      started = 0;
      count = 0;
      motor_stop(ALL); 
    }
  }
  String string_num_right = String(value); 
  int str_right = string_num_right.length() + 1; 
  char char_array_right[str_right];
  string_num_right.toCharArray(char_array_right, str_right);   
  glcd(5, 15, char_array_right);
  
  String string_push_right = String(count); 
  int str_push_right = string_push_right.length() + 1; 
  char char_array_push_right[str_push_right];
  string_push_right.toCharArray(char_array_push_right, str_push_right); 
  glcd(4, 15, char_array_push_right);
  
  
}
