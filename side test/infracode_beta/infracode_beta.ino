#include <ipst.h>


const int pingPin = 29;          //trigger
int inPin = 28;                  //echo

     
void setup() {
  Serial.begin(9600);
  glcdMode(1);
  setTextSize(1);
}
     
void loop()
{
  long duration, cm;
     
  pinMode(pingPin, OUTPUT);
     

  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);

  cm = microsecondsToCentimeters(duration);
  if(cm != 0)
  {
    Serial.print("Right : ");
    Serial.print(cm);
    Serial.print(" cm");
    Serial.println();     
    delay(100);
  }
  
//  glcd(5, 5, cm);
}
     
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
      // The ping travels out and back, so to find the distance of the
      // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
