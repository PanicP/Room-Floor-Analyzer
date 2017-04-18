#include <ipst.h>

int value = 0;
int count, block;

void setup()
{
  Serial.begin(9600);
  motor(1, 10);
  out(18, 1);
  count = 0;
  block = 0;
} 
  
void loop()
{
  value = analog(0);
  
  if(value < 400 && block == 1)
  {
    count ++;
    block = 0;
    Serial.println(count);
    
  }
  if(value > 400 && block == 0)
  {
//    count ++;
    block = 1;
  }
  
}
