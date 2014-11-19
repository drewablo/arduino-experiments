#include <Servo.h>
Servo frontservo,backservo;
char forward[] = {60,100,100,100,100,60,60,60};

/* Ping distance measurement - global variables */
int pingPin = 7;
long int duration, distanceInches;
long distanceFront=0; //cm
int startAvoidanceDistance=20; //cm

long microsecondsToInches(long microseconds)
 {
  return microseconds / 74 / 2;
 }

long microsecondsToCentimeters(long microseconds)
 {
  return microseconds / 29 / 2;
 }

long distanceCm(){ 
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  distanceInches = microsecondsToInches(duration);
  return microsecondsToCentimeters(duration);
}


void setup()
{
frontservo.attach(9);
backservo.attach(10);
frontservo.write(90);
backservo.write(90);

}
void loop()
{
  distanceFront=distanceCm(); 
  if (distanceFront > 1)
  {
   if (distanceFront<startAvoidanceDistance) 
   {
    for(int n=0;n<4;n++)
    {
     frontservo.write(forward[2*n]);
     backservo.write(forward[(2*n)+1]);
     delay(150);
    }
  }
   else
  {
     for(int n=0;n<4;n++)
     {
     backservo.write(forward[2*n]);
     frontservo.write(forward[(2*n)+1]);
     delay(150);
    }
  }
}
}
