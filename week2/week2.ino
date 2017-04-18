#include <ipst.h>

boolean check_front;
int switch_ok;

void setup()
{
  switch_ok = 0;              // ตั้งต้นให้รถยังไม่เริ่มวิ่ง
}

void loop()
{
  if(sw_OK())
  {
    switch_ok = 1;           // กด OK เพื่อให้รถวื่ง
  }
  if(sw1())
  {
    switch_ok = 0;          // กด SW1 เพื่อให้รถหยุด
  }
  if(switch_ok == 1)
  {  
    Forward();            // start
    check_front = digitalRead(30);    // ตรวจข้างหน้า
    if(check_front)                   // ถ้าตรวจข้างหน้าเจอ
    {
      motor_stop(ALL);
      delay(250);
      Backward();
      delay(250);
      motor_stop(ALL);
      delay(250);
      Turn_Left();
      delay(470);
//      Forward();
    }
    
  }
  else
  {
    motor_stop(ALL);
  }
}

void Forward()
{
  motor(1, 25);
  motor(2, 25);
//  sleep(1000);
//  motor_stop(ALL);
//  sleep(1000);
}

void Backward()
{
  motor(1, -15);
  motor(2, -15);
//  sleep(1000);
//  motor_stop(ALL);
//  sleep(1000);
}

void Turn_Left()
{
  motor(1, -20);
  motor(2, 20);
//  sleep(1000);
//  motor_stop(ALL);
//  sleep(1000);
}

void Turn_Right()
{
  motor(1, 20);
  motor(2, -20);
//  sleep(1000);
//  motor_stop(ALL);
//  sleep(1000);
}
