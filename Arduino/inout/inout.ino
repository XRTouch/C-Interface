#include <Servo.h>
#define PINPOT A0

Servo serv;
unsigned char servPos;
unsigned char potVal;
unsigned char lastVal;

void setup()
{
  Serial.begin(9600);
  serv.attach(3);
  pinMode(PINPOT, INPUT);
}

void loop()
{
  if (Serial.available())
  {
    servPos = (unsigned char) map(Serial.read(), 0, 255, 0, 180);
    serv.write(servPos);
  }
  lastVal = potVal;
  potVal = map(analogRead(PINPOT), 0, 1024, 0, 255);
  if (lastVal != potVal)
  {
    Serial.write(potVal);
    lastVal = potVal;
  }
  delay(20);
}
