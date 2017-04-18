#include <ipst.h>

const int pingPin_left = 26;          //trigger อันซ้าย
int inPin_left = 25;                  //echo อันซ้าย
const int pingPin_right = 29;          //trigger อันขวา
int inPin_right = 28;                  //echo อันขวา



boolean check_front;
int switch_ok, turned_left;
int push_right;



void setup()
{
  Serial.begin(9600);
  glcdMode(3);                              // ด้านจอ
  setTextSize(1);                           // ขนาด font
  switch_ok = 0;                            // ตั้งต้นให้รถยังไม่เริ่มวิ่ง
  turned_left = 0;
  push_right = 0;
  
  glcd(1, 1, "Left Infrared : ");
  glcd(1, 20, "cm");
  
  glcd(2, 1, "Right Infrared : ");
  glcd(2, 20, "cm");
  
  glcd(3, 1, "Check Right : ");
}

void loop()
{
  /* ##########################################################*/  
  /* ################## Part : Side Infrared ##################*/
  /* ##########################################################*/
  
  long duration_left; 
  int cm_left;  
  pinMode(pingPin_left, OUTPUT);   
  digitalWrite(pingPin_left, LOW);  

  delayMicroseconds(2);
  
  digitalWrite(pingPin_left, HIGH); 
  
  delayMicroseconds(5);
  
  digitalWrite(pingPin_left, LOW);
  pinMode(inPin_left, INPUT);
  duration_left = pulseIn(inPin_left, HIGH);
  cm_left = microsecondsToCentimeters(duration_left);
  
  if(cm_left != 0)
  {
    Serial.print("Left : ");
    Serial.print(cm_left);
    Serial.print(" cm , ");
    
    String string_num_left = String(cm_left); 
    int str_left = string_num_left.length() + 1; 
    char char_array_left[str_left];
    string_num_left.toCharArray(char_array_left, str_left);   
    
    glcd(1, 19, " ");
//    glcd(1, 1, "Left Infrared : ");
    if(cm_left < 10)
    {
      glcd(1, 17, char_array_left);
      glcd(1, 18, " ");
    }
    else
    {
      glcd(1, 17, char_array_left);
    }
//    glcd(1, 20, "cm");
       
  }
  delay(100);
  
  /* ######################################################################## */
  
  long duration_right;
  int cm_right;
  pinMode(pingPin_right, OUTPUT);
  digitalWrite(pingPin_right, LOW);
  
  delayMicroseconds(2);

  digitalWrite(pingPin_right, HIGH);

  delayMicroseconds(5);

  digitalWrite(pingPin_right, LOW);
  pinMode(inPin_right, INPUT);
  duration_right = pulseIn(inPin_right, HIGH);
  cm_right = microsecondsToCentimeters(duration_right);

  if(cm_right != 0)
  {
    Serial.print("Right : ");
    Serial.print(cm_right);
    Serial.print(" cm");
    Serial.println();
    
    String string_num_right = String(cm_right); 
    int str_right = string_num_right.length() + 1; 
    char char_array_right[str_right];
    string_num_right.toCharArray(char_array_right, str_right);   
    
    glcd(2, 19, " ");
//    glcd(2, 1, "Right Infrared : ");
    if(cm_right < 10)
    {
      glcd(2, 17, char_array_right);
      glcd(2, 18, " ");
    }
    else
    {
      glcd(2, 17, char_array_right);
    }
//    glcd(2, 20, "cm");
       
  }
  delay(100);
  

  /* ###################################################*/  
  /* ################## Part : Moving ##################*/
  /* ###################################################*/  
  
  if(sw_OK())
  {
    switch_ok = 1;           // กด OK เพื่อให้รถวื่ง
  }
  if(sw1())
  {
    switch_ok = 0;          // กด SW1 เพื่อให้รถหยุด
    turned_left = 0;
  }
  if(switch_ok == 1)
  {  
    turned_left = 0;
    Forward();                        // start
    check_front = digitalRead(30);    // ตรวจข้างหน้า
    if(check_front)                   // ถ้าตรวจข้างหน้าเจอ
    {
      motor_stop(ALL);                //หยุดมอเตอร์
      delay(250);
      Backward();                     //ถอยหลัง
      delay(250);
      motor_stop(ALL);                //หยุดมอเตอร์     
      delay(250);
      Turn_Left();                    //เลี้ยวซ้าย
//      turned_left = 1;
      delay(470);
    }
    
    if(in(17) == 0)                   //ถ้าปุ่มด้านขวาถูกกด (ด้านขวาติด ไม่ผ่าน)
    {
      push_right += 1;
      motor_stop(ALL);                //หยุดมอเตอร์
      delay(250);
      Backward();                     //ถอยหลัง
      delay(250);
    }
    
    String string_push_right = String(push_right); 
    int str_push_right = string_push_right.length() + 1; 
    char char_array_push_right[str_push_right];
    string_push_right.toCharArray(char_array_push_right, str_push_right); 
    glcd(3, 15, char_array_push_right);           // print จำนวนครั้งที่ถูกกดออกจอ
    
    
//    if(turned_left == 1)
//    {
//      if(cm_right < 11)                  //เข้าใกล้กำแพง(ด้านขวา)มากเกินไป ให้หันซ้ายออก
//      {
//        Turn_Left();
//        delay(100);
//        Forward();
//      }
//      if(cm_right > 15 && cm_right < 30)                  //ออกจากกำแพง(ด้านขวา)มากเกินไป ให้หันขวาเข้า
//      {
//        Turn_Right();
//        delay(100);
//        Forward();
//      }
//    }
    
  }
  else
  {
    motor_stop(ALL);
  }
  
  
}

  /* #####################################################*/  
  /* ################## Part : Function ##################*/
  /* #####################################################*/

int microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
      // The ping travels out and back, so to find the distance of the
      // object we take half of the distance travelled.
  int temp = microseconds / 29 / 2;
  return temp;
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
